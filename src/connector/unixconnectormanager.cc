#include "connector/unixconnectormanager.hh"
#include "connector/unixconnector.hh"

#include <QMessageBox>

UnixConnectorManager::UnixConnectorManager()
{
    server_ = new QLocalServer();
    if (!server_->listen("/tmp/cute")) {
        QMessageBox::critical(nullptr, tr("CuteStation"),
            tr("Unable to start the local server: %1.")
                .arg(server_->errorString()));
    }

    connect(server_, &QLocalServer::newConnection, this, &UnixConnectorManager::onNewConnection);
}

UnixConnectorManager::~UnixConnectorManager()
{
    delete server_;
}

void UnixConnectorManager::onNewConnection()
{
    UnixConnector* connector = new UnixConnector(server_->nextPendingConnection());
}