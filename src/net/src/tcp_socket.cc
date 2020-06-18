#include "net/tcp_socket.h"

#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "fdbuf.h"

namespace net {

struct tcp_socket::priv {
    int fd = -1;
    fdbuf* buf = nullptr;
};

tcp_socket::tcp_socket()
    : _d(new priv)
{
    _d->fd = ::socket(AF_INET, SOCK_STREAM, 0);
    _d->buf = new fdbuf(_d->fd);
    rdbuf(_d->buf);
}

tcp_socket::tcp_socket(int fd)
    : _d(new priv)
{
    _d->fd = fd;
    _d->buf = new fdbuf(_d->fd);
    rdbuf(_d->buf);
}

tcp_socket::~tcp_socket()
{
    close();
    delete _d->buf;
}

bool tcp_socket::connect(const std::string& host, uint16_t port)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    addr.sin_family = AF_INET;
    if (inet_aton(host.c_str(), &addr.sin_addr) < 0) {
        return false;
    }
    addr.sin_port = htons(port);

    if (::connect(_d->fd, (struct sockaddr*)&addr, len) < 0) {
        return false;
    }

    return true;
}

void tcp_socket::close()
{
    if (_d->buf) {
        ::shutdown(_d->fd, SHUT_RDWR);
        _d->buf->close();
    }
}

}