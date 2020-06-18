#ifndef NET_SOCKET_H_
#define NET_SOCKET_H_

#include <iostream>

namespace net {

class socket : public std::iostream {
public:
    virtual void close() = 0;
};

}
#endif