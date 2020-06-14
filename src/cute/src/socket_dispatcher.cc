#include "socket_dispatcher.h"

#include <QMessageBox>

#include <log/log.h>

#include "socket_connector.h"

namespace cute::io {

SocketDispatcher::SocketDispatcher()
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

    Log::info("SocketDispatcher") << "New connection on socket " << qPrintable(server_->serverName()) << std::endl;
    QLocalSocket* socket = server_->nextPendingConnection();
    SocketConnector* connector = new SocketConnector(socket, thread);
    
    connect(
        this, &SocketDispatcher::connectionClosed,
        connector, &SocketConnector::close
    );

    socket->setParent(connector);
    connector->moveToThread(thread);
    socket->moveToThread(thread);

    thread->start();
}

} // namespaces