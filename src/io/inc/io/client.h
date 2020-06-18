#ifndef CUTE_IO_CLIENT_H_
#define CUTE_IO_CLIENT_H_

#include <memory>

#include <net/socket.h>

namespace cute::io {

class Client {
public:
    Client(std::shared_ptr<net::socket> ios);
    ~Client();

    void run();

private:
    struct Priv;
    std::unique_ptr<Priv> _d;
};

}

#endif