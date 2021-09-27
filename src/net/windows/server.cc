#ifdef _MSC_VER

#include "net/server.hh"

#include <iostream>
#include <memory>

#include <WinSock2.h>
#include <ws2tcpip.h>

#include <log/log.hh>

namespace net {

namespace {
    bool report_and_die(int error)
    {
        char buf[128];
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, buf, sizeof(buf), NULL);
        logging::err("net::server") << buf << logging::tag{"errno", error} << logging::endl;
        return false;
    }
}

struct server::priv {
    SOCKET fd = INVALID_SOCKET;
    std::function<void(net::socket*)> callback = [](net::socket* s) { delete s; };
    std::string path = "";
};

server::server()
    : _d(new priv)
{
}

server::~server()
{
    close();
}

template <>
bool server::listen<tcp>(const std::string& address, uint16_t port)
{
    if (_d->fd != INVALID_SOCKET) {
        close();
    }

    return listen_tcp(address, port);
}

template <>
bool server::listen<unix>(const std::string&, uint16_t)
{
    logging::err("net::socket") << "Unix domain sockets are not supported on windows!" << logging::endl;
    return false;
}

bool server::listen_tcp(const std::string& address, uint16_t port)
{
    SOCKET fd;
    struct sockaddr_in addr;
    int len = sizeof(addr);

    if ((fd = ::socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        return report_and_die(WSAGetLastError());
    }
    _d->fd = fd;

    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, address.c_str(), &addr.sin_addr) < 0) {
        return report_and_die(WSAGetLastError());
    }
    addr.sin_port = htons(port);

    if (bind(fd, (struct sockaddr*)&addr, len) < 0) {;
        return report_and_die(WSAGetLastError());
    }

    if (::listen(fd, 5) < 0) {
        return report_and_die(WSAGetLastError());
    }

    logging::info("net::server") << logging::tag{"addr", address} << "Listening" << logging::endl;

    SOCKET connfd;
    while ((connfd = accept(_d->fd, (struct sockaddr*) &addr, &len)) != INVALID_SOCKET) {
        _d->callback(new net::socket(connfd, tcp));
    }

    return true;
}

void server::close()
{
    if (_d->fd != INVALID_SOCKET) {
        logging::debug("net::server") << "Closing FD" << logging::endl;
        ::shutdown(_d->fd, SD_BOTH);
        ::closesocket(_d->fd);
        _d->fd = INVALID_SOCKET;
    }
}

void server::on_connection(std::function<void(net::socket*)> callback)
{
    _d->callback = callback;
}

} // namespaces

#endif