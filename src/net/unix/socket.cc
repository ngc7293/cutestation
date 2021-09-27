#ifdef __linux__

#include "net/socket.hh"

#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include "sockbuf.hh"

namespace net {

struct socket::priv {
    int fd = -1;
    sockbuf* buf = nullptr;
    socket_type type;
};

socket::socket()
    : closeable(nullptr)
    , _d(new priv)
{
}

socket::socket(int fd, socket_type type)
    : closeable(nullptr)
    , _d(new priv)
{
    _d->fd = fd;
    _d->buf = new sockbuf(fd);
    _d->type = type;
    rdbuf(_d->buf);
}

socket::~socket()
{
    close();
    delete _d->buf;
}

template<socket_type type>
bool socket::connect(const std::string& host, uint16_t port)
{
    if (_d->type != type && _d->buf) {
        delete _d->buf;
        rdbuf(nullptr);
    }

    switch(type) {
    case tcp:
        _d->fd = ::socket(AF_INET, SOCK_STREAM, 0);
        break;
    case unix:
        _d->fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
        break;
    }

    _d->type = type;
    _d->buf = new sockbuf(_d->fd);
    rdbuf(_d->buf);

    switch(type) {
    case tcp:
        return connect_tcp(host, port);
    case unix:
        return connect_unix(host);
    }
}

template bool socket::connect<tcp>(const std::string& host, uint16_t port);
template bool socket::connect<unix>(const std::string& host, uint16_t port);

bool socket::connect_tcp(const std::string& host, uint16_t port)
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

bool socket::connect_unix(const std::string& path)
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

void socket::close()
{
    if (_d->buf) {
        ::shutdown(_d->fd, SHUT_RDWR);
        _d->buf->close();
        setstate(std::ios::eofbit);
    }
}

} // namespaces

#endif