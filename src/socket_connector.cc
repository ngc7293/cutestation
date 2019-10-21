#include "socket_connector.h"

#include <iostream>
#include <chrono>

SocketConnector::SocketConnector(QLocalSocket* socket)
    : socket_(socket)
{
    connect(socket_, &QLocalSocket::readyRead, this, &SocketConnector::readData);
    connect(socket_, &QLocalSocket::disconnected, this, &SocketConnector::close);
}

SocketConnector::~SocketConnector()
{
    socket_->disconnect();
    delete socket_;
}

void SocketConnector::readData()
{
    QByteArray data = socket_->readAll();

    Packet* msg = new Packet();
    msg->ParseFromArray(data.data(), data.size());
    messageReady(msg);
}


void SocketConnector::close()
{
    deleteLater();
}