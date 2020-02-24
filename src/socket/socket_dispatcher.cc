#include "socket/socket_dispatcher.h"

#include <QMessageBox>

#include "socket/socket_connector.h"

SocketDispatcher::SocketDispatcher(PacketIngestor* ingestor)
    : ingestor_(ingestor)
{
    bool failed = false;
    server_ = new QLocalServer();

    if (!server_->listen("/tmp/cute")) {
        if (QLocalServer::removeServer("/tmp/cute")) {
            if (!server_->listen("/tmp/cute")) {
                failed = true;
            }
        } else {
            failed = true;
        }
    }

    if (failed) {
        QMessageBox::critical(nullptr, tr("CuteStation"), tr("Unable to start the local server: %1.").arg(server_->errorString()));
    }

    connect(server_, &QLocalServer::newConnection, this, &SocketDispatcher::openLocalConnection);
}

SocketDispatcher::~SocketDispatcher()
{
    closeAll();
    server_->close();
}

void SocketDispatcher::closeAll()
{
    emit connectionClosed();
}

void SocketDispatcher::openLocalConnection()
{
    QThread* thread = new QThread();
    thread->setObjectName("Connector");

    QLocalSocket* socket = server_->nextPendingConnection();
    SocketConnector* connector = new SocketConnector(socket, thread);

    // Have to use the older SIGNAL()/SLOT() syntax because of abstract multiple-inheritance shenenigans
    connect(dynamic_cast<QObject*>(connector), SIGNAL(packetReady(PacketSP)), dynamic_cast<QObject*>(ingestor_), SLOT(receivePacket(PacketSP)), Qt::DirectConnection);
    connect(this, &SocketDispatcher::connectionClosed, connector, &SocketConnector::close);

    socket->setParent(connector);
    connector->moveToThread(thread);
    socket->moveToThread(thread);

    thread->start();
}