#ifndef NET_SOCKET_HH_
#define NET_SOCKET_HH_

#include <iostream>
#include <memory>

#include "stream.hh"

namespace net {

class socket : public closeable {
public:
    virtual ~socket();
    void close() override;

protected:
    socket(int fd);
    int fd() const;

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif