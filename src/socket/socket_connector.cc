#include "socket/socket_connector.h"

#include <chrono>
#include <iostream>

#include "proto/packet.h"

SocketConnector::SocketConnector(QLocalSocket* socket, QThread* thread)
    : socket_(socket)
{
    connect(socket_, &QLocalSocket::readyRead, this, &SocketConnector::readData);
    connect(socket_, &QLocalSocket::disconnected, this, &SocketConnector::close);
    connect(socket_, &QObject::destroyed, thread, &QThread::terminate);
}

SocketConnector::~SocketConnector()
{
    socket_->disconnect();
}

void SocketConnector::readData()
{
    QByteArray data = socket_->readAll();

    PacketSP msg = std::make_shared<Packet>();
    msg->ParseFromArray(data.data(), data.size());
    emit packetReady(msg);
}

void SocketConnector::close()
{
    deleteLater();
}