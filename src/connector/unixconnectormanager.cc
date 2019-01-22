#include "connector/unixconnectormanager.hh"
#include "connector/unixconnector.hh"

#include <QMessageBox>

UnixConnectorManager::UnixConnectorManager()
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