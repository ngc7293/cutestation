#ifndef CUTE_IO_UNIX_DISPATCHER_HH_
#define CUTE_IO_UNIX_DISPATCHER_HH_

#include "dispatcher.hh"

#include <memory>

namespace cute::io {

// FIXME: Multiple dispatchers using net::server would differ only in the way
// they call listen(). It seems bad design to use multiple classes for this,
// when a simple option flag could be used.
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