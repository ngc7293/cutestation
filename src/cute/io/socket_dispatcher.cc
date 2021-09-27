#include <thread>

#include <log/log.hh>
#include <net/server.hh>
#include <net/socket.hh>
#include <util/thread.hh>

#include "socket_dispatcher.hh"

namespace cute::io {

struct SocketDispatcher::priv {
    net::server server;
    std::thread thread;

    net::socket_type type;
    std::string host;
    uint16_t port;
};

SocketDispatcher::SocketDispatcher()
    : Dispatcher()
    , _d(new priv)
{
}

SocketDispatcher::~SocketDispatcher()
{
    close();
}

void SocketDispatcher::start()
{
    if (_d->thread.joinable()) {
        logging::warn("io::SocketDispatcher") << "Could not start Dispatcher: thread is already running!" << logging::endl;
        return;
    }

    _d->server.on_connection([this](net::socket* socket) {
        std::shared_ptr<net::closeable> ios = std::shared_ptr<net::socket>(socket);
        add(ios);
        clean();
    });

    _d->thread = std::thread([this]() {
        util::thread::rename_this_thread("dispatcher");

        switch (_d->type) {
        case net::unix:
            _d->server.listen<net::unix>(_d->host);
            break;
        case net::tcp:
            _d->server.listen<net::tcp>(_d->host, _d->port);
            break;
        }
    });
}

void SocketDispatcher::close()
{
    _d->server.close();
    if (_d->thread.joinable()) {
        _d->thread.join();
    }

    Dispatcher::close();
}

void SocketDispatcher::set_socket_path(const std::string& path)
{
    _d->type = net::unix;
    _d->host = path;
    _d->port = 0;
}

void SocketDispatcher::set_socket_address(const std::string& host, uint16_t port)
{
    _d->type = net::tcp;
    _d->host = host;
    _d->port = port;
}

}