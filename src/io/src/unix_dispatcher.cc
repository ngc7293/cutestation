#include "io/unix_dispatcher.hh"

#include <thread>

#include <net/unix_server.hh>
#include <net/unix_socket.hh>

namespace cute::io {

struct UnixDispatcher::priv {
    net::unix_server server;
    std::thread thread;
    std::string path;
};

UnixDispatcher::UnixDispatcher(const std::string& path)
    : Dispatcher()
    , _d(new priv)
{
    _d->path = path;
}

UnixDispatcher::~UnixDispatcher()
{
    close();
}

void UnixDispatcher::run()
{
    _d->server.on_connection([this](net::unix_socket* socket) {
        std::shared_ptr<net::closeable> ios = std::shared_ptr<net::unix_socket>(socket);
        add(ios);
        clean();
    });

    _d->thread = std::thread([this]() {
        assert(_d->server.listen(_d->path));
    });
}

void UnixDispatcher::close()
{
    Dispatcher::close();

    _d->server.close();
    if (_d->thread.joinable()) {
        _d->thread.join();
    }
}


}