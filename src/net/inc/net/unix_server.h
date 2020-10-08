#ifndef NET_UNIX_SERVER_H_
#define NET_UNIX_SERVER_H_

#include <functional>
#include <memory>
#include <string>

#include "unix_socket.h"

namespace net {

/** Unix local socket server
 *
 * Will accept() new connections once listened is called, and call the
 * on_connection callback with a unix_socket each time.
 *
 * Note that you MUST take owner ship of the created unix_socket or you WILL
 * leak memory. If on_connection is not set, default handler will simply delete
 * the socket, shutting down the connection.
 */
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