#ifndef NET_TCP_SERVER_HH_
#define NET_TCP_SERVER_HH_

#include <functional>
#include <memory>
#include <string>

#include <cstdint>

#include "tcp_socket.hh"

namespace net {

/** TCP socket server
 *
 * Will accept() new connections once listened is called, and call the
 * on_connection callback with a tcp_socket each time.
 *
 * Note that you MUST take owner ship of the created tcp_socket or you WILL leak
 * memory. If on_connection is not set, default handler will simply delete the
 * socket, shutting down the connection.
 */
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