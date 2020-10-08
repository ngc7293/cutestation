#ifndef NET_SOCKET_HH_
#define NET_SOCKET_HH_

#include <iostream>
#include <memory>

namespace net {

class socket : public std::iostream {
public:
    virtual ~socket();
    virtual void close();

protected:
    socket(int fd);
    int fd() const;

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}
#endif