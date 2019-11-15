#ifndef SOCKET_CONNECTOR_H_
#define SOCKET_CONNECTOR_H_

#include <QObject>
#include <QLocalSocket>

#include "proto/packet.pb.h"


class SocketConnector : public QObject {
    Q_OBJECT

private:
    QLocalSocket* socket_;

public:
    SocketConnector(QLocalSocket* socket);
    ~SocketConnector();

private slots:
    void readData();

public slots:
    void close();

signals:
    void messageReady(Packet* msg);
    void connectionClosed();
};

#endif