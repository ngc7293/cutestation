#ifndef CUTE_IO_UNIX_DISPATCHER_HH_
#define CUTE_IO_UNIX_DISPATCHER_HH_

#include "dispatcher.hh"

#include <memory>

namespace cute::io {

class UnixDispatcher : public Dispatcher {
public:
    UnixDispatcher(const std::string& path);
    virtual ~UnixDispatcher();

    void run() override;
    void close() override;

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif