#ifndef SOCKBUF_HH_
#define SOCKBUF_HH_

#include <streambuf>

#include <cstdio>

#include <WinSock2.h>

namespace net {

class sockbuf : public std::streambuf {
    struct priv;

public:
    sockbuf(SOCKET fd, int len = 128);
    virtual ~sockbuf();

    int overflow(int c = EOF) override;
    int underflow() override;
    int sync() override;

    bool close();

private:
    SOCKET _fd;

    char* _garea;
    char* _parea;
    int _len;
};

} // namespaces

#endif