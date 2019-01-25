#ifndef UNIX_CONNECTION_HH
#define UNIX_CONNECTION_HH

#include "connection.hh"

#include <QLocalSocket>

/**
 * Unix Local Domain Socket connection
 */
class UnixConnection : public Connection {
private:
    QLocalSocket* socket_;

public:
    UnixConnection(QLocalSocket* socket);
    virtual ~UnixConnection();

private slots:
    void onReadyRead();
};

#endif