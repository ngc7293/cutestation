#include "net/unix_server.h"

#include <iostream>
#include <memory>

#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/stat.h>

#include <log/log.h>

#include "net/tcp_socket.h"

#ifndef __linux__
#error This file should only be compiled on Linux! Check your CMakeLists.
#endif

namespace net {

struct unix_server::priv {
    int fd = -1;
    std::string name;
    std::function<void(net::unix_socket*)> callback = [](net::unix_socket* s) { delete s; };
};

unix_server::unix_server()
    : _d(new priv)
{
}

unix_server::~unix_server()
{
    close();
}

bool unix_server::listen(const std::string& path)
{
    int sockfd;
    struct sockaddr_un addr;
    socklen_t len = sizeof(addr);

    if ((sockfd = ::socket(AF_UNIX, SOCK_SEQPACKET, 0)) < 0) {
        return false;
    }
    _d->fd = sockfd;

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path.c_str(), sizeof(addr.sun_path)-1);

    struct stat res;
    if (stat(path.c_str(), &res) == 0) {
        remove(path.c_str());
    }

    if (bind(sockfd, (struct sockaddr*)&addr, len) < 0) {
        return false;
    }
    _d->name = path;

    if (::listen(sockfd, 5) < 0) {
        return false;
    }

    int connfd;
    while ((connfd = accept(_d->fd, (struct sockaddr*) &addr, &len)) > 0) {
        _d->callback(new net::unix_socket(connfd));
    }

    return true;
}

void unix_server::close()
{
    Log::debug("unix_server/" + _d->name) << "Closing" << std::endl;
    if (_d->fd > 0) {
        Log::debug("unix_server/" + _d->name) << "Closing FD" << std::endl;
        ::shutdown(_d->fd, SHUT_RDWR);
        ::close(_d->fd);
        _d->fd = -1;
    }

    if (_d->name != "") {
        Log::debug("unix_server/" + _d->name) << "Removing socket file" << std::endl;
        ::unlink(_d->name.c_str());
        ::remove(_d->name.c_str());
        _d->name = "";
    }
}

void unix_server::on_connection(std::function<void(net::unix_socket*)> callback)
{
    _d->callback = callback;
}

}