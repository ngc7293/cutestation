#include "rpc/connection/unixconnectionmanager.hh"

#include <QMessageBox>

#include "rpc/connection/connectionmanager.hh"
#include "rpc/connection/unixconnection.hh"

UnixConnectionManager::UnixConnectionManager()
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

    connect(server_, &QLocalServer::newConnection, this, &UnixConnectionManager::onLocalConnection);
}

UnixConnectionManager::~UnixConnectionManager()
{
    delete server_;
}

void UnixConnectionManager::onLocalConnection()
{
    ConnectionManager::get().open(new UnixConnection(server_->nextPendingConnection()));
}