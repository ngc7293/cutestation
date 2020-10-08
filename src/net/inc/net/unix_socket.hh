#ifndef NET_UNIX_SOCKET_HH_
#define NET_UNIX_SOCKET_HH_

#include "socket.hh"

#include <string>

namespace net {

class unix_socket: public net::socket {
public:
    unix_socket();
    virtual ~unix_socket();

    bool connect(const std::string& path);

private:
    friend class unix_server;
    unix_socket(int fd);
};

}

#endif