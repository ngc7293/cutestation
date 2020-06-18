#include "net/unix_socket.h"

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "fdbuf.h"

namespace net {

struct unix_socket::priv {
    int fd = -1;
    fdbuf* buf = nullptr;
};

unix_socket::unix_socket()
    : _d(new priv)
{
    _d->fd = ::socket(AF_UNIX, SOCK_SEQPACKET, 0);
    _d->buf = new fdbuf(_d->fd);
    rdbuf(_d->buf);
}

unix_socket::unix_socket(int fd)
    : _d(new priv)
{
    _d->fd = fd;
    _d->buf = new fdbuf(_d->fd);
    rdbuf(_d->buf);
}

unix_socket::~unix_socket()
{
    close();
    delete _d->buf;
}

bool unix_socket::connect(const std::string& path)
{
    struct sockaddr_un addr;
    socklen_t len = sizeof(addr);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, path.c_str());

    if (::connect(_d->fd, (struct sockaddr*)&addr, len) < 0) {
        return false;
    }

    return true;
}

void unix_socket::close()
{
    if (_d->buf) {
        ::shutdown(_d->fd, SHUT_RDWR);
        _d->buf->close();
        setstate(std::ios::eofbit);
    }
}

}