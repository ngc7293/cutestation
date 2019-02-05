#ifndef CONNECTOR_MANAGER_HH
#define CONNECTOR_MANAGER_HH

#include <vector>

#include "connection.hh"

class ConnectionManager {
private:
    std::vector<Connection*> connections_;

public:
    static ConnectionManager& get();
    ~ConnectionManager();

    void open(Connection* connection);
    void close(Connection* connection);
    void closeAll();

private:
    ConnectionManager();
};

#endif