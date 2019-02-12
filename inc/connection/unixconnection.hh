#ifndef UNIX_CONNECTION_HH_
#define UNIX_CONNECTION_HH_

#include "connection.hh"

#include <QLocalSocket>

#include "data/data.hh"

/**
 * Unix Local Domain Socket connection
 */
class UnixConnection : public Connection {
    Q_OBJECT

private:
    QLocalSocket* socket_;

public:
    UnixConnection(QLocalSocket* socket);
    virtual ~UnixConnection();

private slots:
    void onReadyRead();
};

#endif // UNIX_CONNECTION_HH_