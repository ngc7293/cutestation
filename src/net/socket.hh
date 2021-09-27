#ifndef NET_SOCKET_HH_
#define NET_SOCKET_HH_

#include <iostream>
#include <memory>

#include "stream.hh"

#if (defined _MSC_VER)
#include <WinSock2.h>
#endif

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
    friend class server;
#if (defined _MSC_VER)
    socket(SOCKET fd, socket_type type);
#else
    socket(int fd, socket_type type);
#endif

private:
    bool connect_tcp(const std::string& path, uint16_t port);
#if (not defined _MSC_VER)
    bool connect_unix(const std::string& path);
#endif

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif