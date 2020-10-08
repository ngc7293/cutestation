#include "net/unix_socket.hh"

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "fdbuf.hh"

namespace net {

unix_socket::unix_socket()
    : socket(::socket(AF_UNIX, SOCK_SEQPACKET, 0))
{
}

unix_socket::unix_socket(int fd)
    : socket(fd)
{
}

unix_socket::~unix_socket()
{
}

bool unix_socket::connect(const std::string& path)
{
    struct sockaddr_un addr;
    socklen_t len = sizeof(addr);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, path.c_str());

    if (::connect(fd(), (struct sockaddr*)&addr, len) < 0) {
        return false;
    }

    return true;
}

}