#ifndef UNIX_CONNECTOR_HH
#define UNIX_CONNECTOR_HH

#include "connector.hh"

#include <QLocalSocket>

/**
 * Unix Local Domain Socket connector
 */
class UnixConnector : public Connector {
private:
    QLocalSocket* socket_;

public:
    UnixConnector(QLocalSocket* socket);
    virtual ~UnixConnector();
};

#endif