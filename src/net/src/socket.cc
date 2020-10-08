#include "net/socket.hh"

#include <sys/socket.h>

#include "fdbuf.hh"

namespace net {

struct socket::priv {
    int fd = -1;
    fdbuf* buf = nullptr;
};

socket::socket(int fd)
    : _d(new priv)
{
    _d->fd = fd;
    _d->buf = new fdbuf(fd);
    rdbuf(_d->buf);
}

socket::~socket()
{
    close();
    delete _d->buf;
}

void socket::close()
{
    if (_d->buf) {
        ::shutdown(_d->fd, SHUT_RDWR);
        _d->buf->close();
        setstate(std::ios::eofbit);
    }
}

int socket::fd() const
{
    return _d->fd;
}

}