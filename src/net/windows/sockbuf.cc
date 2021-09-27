#ifdef _MSC_VER

#include "sockbuf.hh"

#include <iostream>

#include <WinSock2.h>

namespace net {

sockbuf::sockbuf(SOCKET fd, int len)
{
    _fd = fd;
    _garea = new char[len];
    _parea = new char[len];
    _len = len;

    setp(_parea, _parea + _len);
}

sockbuf::~sockbuf()
{
    delete[] _garea;
    delete[] _parea;
}

int sockbuf::overflow(int c)
{
    if (sync() == -1) {
        return traits_type::eof();
    }

    sputc(traits_type::to_char_type(c));
    return c;
}

int sockbuf::underflow()
{
    int count = recv(_fd, _garea, _len, 0);

    if (count == SOCKET_ERROR) {
        return traits_type::eof();
    }

    setg(_garea, _garea, _garea + count);
    return traits_type::to_int_type(_garea[0]);
}

int sockbuf::sync()
{
    if (send(_fd, _parea, static_cast<int>(pptr() - pbase()), 0) == -1) {
        return -1;
    }

    setp(_parea, _parea + _len);
    return 0;
}

bool sockbuf::close()
{
    return (closesocket(_fd) == 0);
}

} // namespaces

#endif