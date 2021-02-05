#ifndef CUTE_IO_UNIX_DISPATCHER_HH_
#define CUTE_IO_UNIX_DISPATCHER_HH_

#include "dispatcher.hh"

#include <memory>

namespace cute::io {

// FIXME: Multiple dispatchers using net::server would differ only in the way
// they call listen(). It seems bad design to use multiple classes for this,
// when a simple option flag could be used.
class SocketDispatcher : public Dispatcher {
public:
    SocketDispatcher();
    virtual ~SocketDispatcher();

    void start() override;
    void close() override;

    /** set_socket_path
     * Sets the socket's filesystem path. This automatically switches the
     * socket type to Unix, but doesn't affect currently running (start()'d)
     * instances
     * 
     * @param path local path in filesystem
     */
    void set_socket_path(const std::string& path);

    /** set_socket_address
     * Sets the socket's binding address and port, automatically marking this
     * Dispatcher as a TCP socket dispatcher. This does not affect already
     * started instances.
     * 
     * @param host IPv4 address to bind to
     * @param port Port to listen on
     */
    void set_socket_address(const std::string& host, uint16_t port);

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif