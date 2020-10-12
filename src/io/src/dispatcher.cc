#include "io/dispatcher.hh"

#include <thread>

#include "io/client.hh"

namespace cute::io {

struct ClientThread {
    std::thread thread;
    std::shared_ptr<Client> client;

    ClientThread(std::shared_ptr<Client> client)
        : thread(&Client::run, client.get())
        , client(client)
    {
    }
};

struct Dispatcher::priv {
    std::vector<ClientThread> clients;
};

Dispatcher::Dispatcher()
    : _d(new priv)
{
}

Dispatcher::~Dispatcher()
{
    close();
}

void Dispatcher::add(std::shared_ptr<net::closeable> stream)
{
    std::shared_ptr<Client> client = std::make_shared<Client>(stream);
    _d->clients.emplace_back(client);
}

void Dispatcher::clean()
{
    for (auto it = _d->clients.begin(); it != _d->clients.end(); it++) {
        if (it->client->done()) {
            it->thread.join();
            _d->clients.erase(it);
        }
    }
}

void Dispatcher::close()
{
    while (_d->clients.size()) {
        auto& ct = _d->clients.front();
        ct.client->close();
        ct.thread.join();
        _d->clients.erase(_d->clients.begin());
    }
}

}