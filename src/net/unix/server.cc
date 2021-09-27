#ifdef __linux__

#include "net/server.hh"

#include <iostream>
#include <memory>

#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/stat.h>

#include <log/log.hh>

namespace net {

namespace {
    bool report_and_die(int error)
    {
        logging::err("net::server") << strerror(error) << logging::tag{"errno", error} << logging::endl;
        return false;
    }
}

struct server::priv {
    int fd = -1;
    std::function<void(net::socket*)> callback = [](net::socket* s) { delete s; };
    std::string path = "";
};

server::server()
    : _d(new priv)
{
}

server::~server()
{
    close();
}

template<socket_type type>
bool server::listen(const std::string& address, uint16_t port)
{
    if (_d->fd != -1) {
        close();
    }

    switch (type) {
        case tcp:
            return listen_tcp(address, port);
        case unix:
            return listen_unix(address);
    }
}

template bool server::listen<tcp>(const std::string& address, uint16_t port);
template bool server::listen<unix>(const std::string& address, uint16_t port);

bool server::listen_tcp(const std::string& address, uint16_t port)
{
    int sockfd;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    if ((sockfd = ::socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return report_and_die(errno);
    }
    _d->fd = sockfd;

    int option = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    addr.sin_family = AF_INET;
    if (inet_aton(address.c_str(), &addr.sin_addr) < 0) {
        return report_and_die(errno);
    }
    addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&addr, len) < 0) {;
        return report_and_die(errno);
    }

    if (::listen(sockfd, 5) < 0) {
        return report_and_die(errno);
    }

    logging::info("net::server") << logging::tag{"addr", address} << "Listening" << logging::endl;

    int connfd;
    while ((connfd = accept(_d->fd, (struct sockaddr*) &addr, &len)) > 0) {
        _d->callback(new net::socket(connfd, tcp));
    }

    return true;
}

bool server::listen_unix(const std::string& path)
{
    int sockfd;
    struct sockaddr_un addr;
    socklen_t len = sizeof(addr);

    if ((sockfd = ::socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        return report_and_die(errno);
    }
    _d->fd = sockfd;

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path.c_str(), sizeof(addr.sun_path)-1);

    struct stat res;
    if (stat(path.c_str(), &res) == 0) {
        remove(path.c_str());
    }

    if (bind(sockfd, (struct sockaddr*)&addr, len) < 0) {
        return report_and_die(errno);
    }
    _d->path = path;

    if (::listen(sockfd, 5) < 0) {
        return report_and_die(errno);
    }

    logging::info("net::server") << logging::tag{"path", path} << "Listening" << logging::endl;

    int connfd;
    while ((connfd = accept(_d->fd, (struct sockaddr*) &addr, &len)) > 0) {
        _d->callback(new net::socket(connfd, unix));
    }

    return true;
}

void server::close()
{
    if (_d->fd > 0) {
        logging::debug("net::server") << "Closing FD" << logging::endl;
        ::shutdown(_d->fd, SHUT_RDWR);
        ::close(_d->fd);
        _d->fd = -1;
    }

    if (_d->path != "") {
        logging::debug("net::server") << logging::tag{"path", _d->path} << "Removing socket file" << logging::endl;
        ::unlink(_d->path.c_str());
        ::remove(_d->path.c_str());
        _d->path = "";
    }
}

void server::on_connection(std::function<void(net::socket*)> callback)
{
    _d->callback = callback;
}

} // namespaces

#endif