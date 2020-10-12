#ifndef NET_SERVER_HH_
#define NET_SERVER_HH_

#include <functional>
#include <memory>
#include <string>

#include <cstdint>

#include "socket.hh"

namespace net {

/** Socket server
 *
 * Will accept() new connections once listen() is called, and call the
 * on_connection callback with a net::socket each time a new connection is
 * available.
 *
 * Note that you MUST take owner ship of the created socket or you WILL leak
 * memory. If on_connection is not set, default handler will simply delete the
 * socket, shutting down the connection.
 */
class server {
public:
    server();
    ~server();

    template<socket_type type>
    bool listen(const std::string& address, uint16_t port = 0);
    void close();

    void on_connection(std::function<void(net::socket*)> callback);

private:
    bool listen_tcp(const std::string& address, uint16_t port);
    bool listen_unix(const std::string& path);

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif