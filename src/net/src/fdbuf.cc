#include "fdbuf.h"

#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

fdbuf::fdbuf(int fd, std::size_t len)
{
    _fd = fd;
    _garea = new char[len];
    _parea = new char[len];
    _len = len;

    setp(_parea, _parea + _len);
}

fdbuf::~fdbuf()
{
    delete _garea;
    delete _parea;
}

int fdbuf::overflow(int c)
{
    if (sync() == -1) {
        return traits_type::eof();
    }

    sputc(traits_type::to_char_type(c));
    return c;
}

int fdbuf::underflow()
{
    ssize_t count = read(_fd, _garea, _len);

    if (count <= 0) {
        return traits_type::eof();
    }

    setg(_garea, _garea, _garea + count);
    return traits_type::to_int_type(_garea[0]);
}

int fdbuf::sync()
{
    if (send(_fd, _parea, (pptr() - pbase()), MSG_NOSIGNAL) == -1) {
        return -1;
    }

    setp(_parea, _parea + _len);
    return 0;
}

bool fdbuf::close()
{
    return (::close(_fd) == 0);
}