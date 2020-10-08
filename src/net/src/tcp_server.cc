#include "net/tcp_server.h"

#include <iostream>
#include <memory>

#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "net/tcp_socket.h"

#ifndef __linux__
#error This file should only be compiled on Linux! Check your CMakeLists.
#endif

namespace net {

struct tcp_server::priv {
    int fd = -1;
    std::function<void(net::tcp_socket*)> callback = [](net::tcp_socket* s) { delete s; };
};

tcp_server::tcp_server()
    : _d(new priv)
{
}

tcp_server::~tcp_server()
{
    close();
}

bool tcp_server::listen(const std::string& address, uint16_t port)
{
    int sockfd;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    if ((sockfd = ::socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return false;
    }

    addr.sin_family = AF_INET;
    if (inet_aton(address.c_str(), &addr.sin_addr) < 0) {
        return false;
    }
    addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&addr, len) < 0) {;
        return false;
    }

    if (::listen(sockfd, 5) < 0) {
        return false;
    }

    _d->fd = sockfd;

    int connfd;
    while ((connfd = accept(_d->fd, (struct sockaddr*) &addr, &len)) > 0) {
        _d->callback(new net::tcp_socket(connfd));
    }

    return true;
}

void tcp_server::close()
{
    if (_d->fd > 0) {
        ::shutdown(_d->fd, SHUT_RDWR);
        ::close(_d->fd);
    }
}

void tcp_server::on_connection(std::function<void(net::tcp_socket*)> callback)
{
    _d->callback = callback;
}

}