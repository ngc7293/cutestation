#ifndef SOCKET_DISPATCHER_H_
#define SOCKET_DISPATCHER_H_

#include <QLocalServer>

#include "proto/packet.h"

namespace cute::io {

class SocketDispatcher : public QObject {
    Q_OBJECT

private:
    QLocalServer* server_;

public:
    SocketDispatcher();
    ~SocketDispatcher();

public slots:
    void closeAll();

private slots:
    void openLocalConnection();

signals:
    void connectionClosed();

};

} // namespaces

#endif // UNIX_CONNECTOR_MANAGER_H_