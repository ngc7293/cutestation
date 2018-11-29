#include "source/source.hh"

#include <cstdlib>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <QDateTime>

#include "data/data.hh"
#include "lib/json.hh"

Source::Source(std::string path)
{
    quit_ = false;
    struct sockaddr_un addr;

    if ((sockfd_ = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path.c_str(), sizeof(addr.sun_path) - 1);

    if (unlink(path.c_str()) == -1) {
        perror("unlink error");
        exit(-1);
    }

    if (bind(sockfd_, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind error");
        exit(-1);
    }

    if (listen(sockfd_, 1) == -1) {
        perror("listen error");
        exit(-1);
    }
}

Source::~Source()
{
}

void Source::run()
{
    int cl, rc;
    char buf[128] = { 0 };

    while (!quit_) {
        if ((cl = accept(sockfd_, NULL, NULL)) == -1) {
            perror("accept error");
            continue;
        }

        while ((rc = read(cl, buf, sizeof(buf))) > 0) {
            Data* data = new Data(QDateTime::currentMSecsSinceEpoch());
            data->setValue(atoi(buf));
            emit dataReady(data);
        }

        if (rc == 0) {
            close(cl);
        }
    }

    emit finished();
}