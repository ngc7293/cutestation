#ifndef CUTE_IO_DISPATCHER_HH_
#define CUTE_IO_DISPATCHER_HH_

#include <memory>

#include "client.hh"

namespace cute::io {

class Dispatcher {
public:
    Dispatcher();
    virtual ~Dispatcher();

    virtual void run() = 0;
    void close();

protected:
    void add(std::shared_ptr<net::closeable> stream);

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif