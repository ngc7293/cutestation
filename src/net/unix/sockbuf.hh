#ifndef NET_UNIX_SOCKBUF_HH_
#define NET_UNIX_SOCKBUF_HH_

#ifdef __linux__

#include <streambuf>

#include <cstdio>

namespace net {

class sockbuf : public std::streambuf {
    struct priv;

public:
    sockbuf(int fd, std::size_t len = 128);
    virtual ~sockbuf();

    int overflow(int c = EOF) override;
    int underflow() override;
    int sync() override;

    bool close();

private:
    int _fd;

    char* _garea;
    char* _parea;
    size_t _len;
};

} // namespaces

#endif
#endif