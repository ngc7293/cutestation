#include "socket/socket_connector.h"

#include <chrono>
#include <iostream>

#include "proto/packet.h"

SocketConnector::SocketConnector(QLocalSocket *socket) : socket_(socket) {
  connect(socket_, &QLocalSocket::readyRead, this, &SocketConnector::readData);
  connect(socket_, &QLocalSocket::disconnected, this, &SocketConnector::close);
}

SocketConnector::~SocketConnector() {
  socket_->disconnect();
  delete socket_;
}

void SocketConnector::readData() {
  QByteArray data = socket_->readAll();

  PacketSP msg = std::make_shared<Packet>();
  msg->ParseFromArray(data.data(), data.size());
  messageReady(msg);
}

void SocketConnector::close() { deleteLater(); }