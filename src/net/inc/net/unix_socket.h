#ifndef NET_UNIX_SOCKET_H_
#define NET_UNIX_SOCKET_H_

#include "socket.h"

#include <iostream>
#include <memory>
#include <string>

#include <cstdint>

namespace net {

class unix_socket: public net::socket {
public:
    unix_socket();
    virtual ~unix_socket();

    bool connect(const std::string& path);
    void close() override;

private:
    friend class unix_server;
    unix_socket(int fd);

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif