#include "net/tcp_socket.hh"

#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "fdbuf.hh"

namespace net {

tcp_socket::tcp_socket()
    : socket(::socket(AF_INET, SOCK_STREAM, 0))
{

}

tcp_socket::tcp_socket(int fd)
    : socket(fd)
{
}

tcp_socket::~tcp_socket()
{
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

    if (::connect(fd(), (struct sockaddr*)&addr, len) < 0) {
        return false;
    }

    return true;
}

}