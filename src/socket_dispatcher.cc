#include "socket_dispatcher.h"

#include <QMessageBox>

#include "socket_connector.h"

SocketDispatcher::SocketDispatcher(MessageIngestor* ingestor)
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
        QMessageBox::critical(
            nullptr,
            tr("CuteStation"),
            tr("Unable to start the local server: %1.").arg(server_->errorString())
        );
    }

    connect(server_, &QLocalServer::newConnection, this, &SocketDispatcher::openLocalConnection);
}

SocketDispatcher::~SocketDispatcher()
{
    closeAll();
    server_->close();
    delete server_;
}

void SocketDispatcher::closeAll()
{
    connectionClosed();
}

void SocketDispatcher::openLocalConnection()
{
    SocketConnector* connector = new SocketConnector(server_->nextPendingConnection());
    connect(connector, &SocketConnector::messageReady, ingestor_, &MessageIngestor::receiveMessage);
    connect(this, &SocketDispatcher::connectionClosed, connector, &SocketConnector::close);
}