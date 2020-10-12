#ifndef NET_SOCKET_HH_
#define NET_SOCKET_HH_

#include <iostream>
#include <memory>

#include "stream.hh"

namespace net {

#undef unix
enum socket_type {
    tcp,
    unix
};

class socket : public closeable {
public:
    socket();
    ~socket();

    template<socket_type type>
    bool connect(const std::string& host, uint16_t port = 0);
    void close() override;

protected:
    friend class unix_server;
    friend class tcp_server;
    socket(int fd, socket_type type);

private:
    bool connect_tcp(const std::string& path, uint16_t port);
    bool connect_unix(const std::string& path);

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif