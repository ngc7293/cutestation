#include "rpc/connection/connectionmanager.hh"

ConnectionManager::ConnectionManager()
{
}

ConnectionManager::~ConnectionManager()
{
}

ConnectionManager& ConnectionManager::get()
{
    static ConnectionManager* instance_;
    if (!instance_) {
        instance_ = new ConnectionManager();
    }
    return *instance_;
}

void ConnectionManager::open(Connection* connection)
{
    connections_.push_back(connection);
}

void ConnectionManager::close(Connection* connection)
{
    for (std::vector<Connection*>::iterator it = connections_.begin(); it != connections_.end(); it++) {
        if (*it == connection) {
            delete *it;
            connections_.erase(it);
            return;
        }
    }
}

void ConnectionManager::closeAll()
{
    for (Connection* connection : connections_) {
        delete connection;
    }

    connections_.clear();
}
