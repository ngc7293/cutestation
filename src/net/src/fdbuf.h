#ifndef FDBUF_H_
#define FDBUF_H_

#include <streambuf>

#include <cstdio>

class fdbuf : public std::streambuf {
    struct priv;

public:
    fdbuf(int fd, std::size_t len = 128);
    virtual ~fdbuf();

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

#endif