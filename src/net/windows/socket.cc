#ifdef _MSC_VER

#include "net/socket.hh"

#include <WinSock2.h>
#include <ws2tcpip.h>

#include <log/log.hh>

#include "sockbuf.hh"

namespace net {

struct socket::priv {
    SOCKET fd = INVALID_SOCKET;
    sockbuf* buf = nullptr;
    socket_type type;
};

socket::socket()
    : closeable(nullptr) 
    ,_d(new priv)
{
}

socket::socket(SOCKET fd, socket_type type)
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
    if (_d->buf) {
        delete _d->buf;
    }
}

template<>
bool socket::connect<tcp>(const std::string& host, uint16_t port)
{
    if (_d->buf) {
        delete _d->buf;
        rdbuf(nullptr);
    }

    _d->fd = ::socket(AF_INET, SOCK_STREAM, 0);
    _d->type = tcp;
    _d->buf = new sockbuf(_d->fd);
    rdbuf(_d->buf);

    return connect_tcp(host, port);
}

template<>
bool socket::connect<unix>(const std::string&, uint16_t)
{
    logging::err("net::socket") << "Unix domain sockets are not supported on windows!" << logging::endl;
    return false;
}

bool socket::connect_tcp(const std::string& host, uint16_t port)
{
    struct sockaddr_in addr;
    int len = sizeof(addr);

    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) < 0) {
        return false;
    }
    addr.sin_port = htons(port);

    if (::connect(_d->fd, (struct sockaddr*)&addr, len) < 0) {
        return false;
    }

    return true;
}


void socket::close()
{
    if (_d->buf) {
        ::shutdown(_d->fd, SD_BOTH);
        _d->buf->close();
        setstate(std::ios::eofbit);
    }
}

} // namespaces

#endif