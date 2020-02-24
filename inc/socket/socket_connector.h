#ifndef SOCKET_CONNECTOR_H_
#define SOCKET_CONNECTOR_H_

#include <QObject>
#include <QLocalSocket>
#include <QThread>

#include "proto/packet.h"


class SocketConnector : public QObject, public PacketEmitter, public PacketIngestor {
    Q_OBJECT
    Q_INTERFACES(PacketEmitter)
    Q_INTERFACES(PacketIngestor)

private:
    QLocalSocket* socket_;

public:
    SocketConnector(QLocalSocket* socket, QThread* thread);
    ~SocketConnector();

private slots:
    void readData();

public slots:
    void close();
    void receivePacket(PacketSP packet) override { };

signals:
    void packetReady(PacketSP packet) override;
    void connectionClosed();
};

#endif