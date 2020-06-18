#ifndef NET_UNIX_SERVER_H_
#define NET_UNIX_SERVER_H_

#include <functional>
#include <memory>
#include <string>

#include "unix_socket.h"

namespace net {

class unix_server {
public:
    unix_server();
    ~unix_server();

    bool listen(const std::string& path);
    void close();

    void on_connection(std::function<void(net::unix_socket*)> callback);

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif