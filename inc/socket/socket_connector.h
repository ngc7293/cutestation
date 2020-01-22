#ifndef SOCKET_CONNECTOR_H_
#define SOCKET_CONNECTOR_H_

#include <QObject>
#include <QLocalSocket>
#include <QThread>

#include "proto/packet.h"


class SocketConnector : public QObject {
    Q_OBJECT

private:
    QLocalSocket* socket_;

public:
    SocketConnector(QLocalSocket* socket, QThread* thread);
    ~SocketConnector();

private slots:
    void readData();

public slots:
    void close();

signals:
    void messageReady(PacketSP msg);
    void connectionClosed();
};

#endif