#ifndef NET_TCP_SERVER_H_
#define NET_TCP_SERVER_H_

#include <functional>
#include <memory>
#include <string>

#include <cstdint>

#include "tcp_socket.h"

namespace net {

class tcp_server {
public:
    tcp_server();
    ~tcp_server();

    bool listen(const std::string& address, uint16_t port);
    void close();

    void on_connection(std::function<void(net::tcp_socket*)> callback);

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif