#ifndef NET_TCP_SOCKET_HH_
#define NET_TCP_SOCKET_HH_

#include "socket.hh"

#include <iostream>
#include <memory>
#include <string>

namespace net {

class tcp_socket : public net::socket {
public:
    tcp_socket();
    virtual ~tcp_socket();

    bool connect(const std::string& host, uint16_t port);
    void close() override;

private:
    friend class tcp_server;
    tcp_socket(int fd);

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif