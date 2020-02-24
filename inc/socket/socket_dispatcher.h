#ifndef SOCKET_DISPATCHER_H_
#define SOCKET_DISPATCHER_H_

#include <QLocalServer>

#include "proto/packet.h"

class SocketDispatcher : public QObject {
    Q_OBJECT

private:
    QLocalServer* server_;
    PacketIngestor* ingestor_;

public:
    SocketDispatcher(PacketIngestor* ingestor);
    ~SocketDispatcher();

public slots:
    void closeAll();

private slots:
    void openLocalConnection();

signals:
    void connectionClosed();

};

#endif // UNIX_CONNECTOR_MANAGER_H_