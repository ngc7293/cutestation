#ifndef NET_SOCKET_HH_
#define NET_SOCKET_HH_

#include <iostream>

namespace net {

class socket : public std::iostream {
public:
    virtual void close() = 0;
};

}
#endif