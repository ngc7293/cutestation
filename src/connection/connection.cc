#include "connection/connection.hh"

#include <iostream>

#include "connection/connectionmanager.hh"
#include "distributor.hh"

Connection::Connection()
{
    connect(this, &Connection::dataReady, &(Distributor::get()), &Distributor::onData);
    connect(this, &Connection::closed, this, &QObject::deleteLater);
}

Connection::~Connection()
{
}

void Connection::onClose()
{
    ConnectionManager::get().close(this);
    emit closed(this);
}