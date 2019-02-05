#ifndef UNIX_CONNECTION_HH
#define UNIX_CONNECTION_HH

#include "connection.hh"

#include <QLocalSocket>

#include "messages/message.hh"

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

signals:
    void messageReady(Message* message);
};

#endif