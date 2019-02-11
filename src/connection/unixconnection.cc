#include "connection/unixconnection.hh"

#include <iostream>

#include <QLocalSocket>
#include <QString>

#include "lib/rapidjson/document.h"

#include "messages/message.hh"
#include "distributor.hh"

UnixConnection::UnixConnection(QLocalSocket* socket)
    : Connection()
    , socket_(socket)
{
    connect(socket_, &QLocalSocket::readyRead, this, &UnixConnection::onReadyRead);
    connect(socket_, &QLocalSocket::disconnected, this, &UnixConnection::deleteLater);
    connect(this, &UnixConnection::messageReady, &(Distributor::get()), &Distributor::onMessage);
}

UnixConnection::~UnixConnection()
{
    socket_->disconnectFromServer();
    delete socket_;
}

void UnixConnection::onReadyRead()
{
    uint64_t length = 0;
    while (true) {
        QString line = QString::fromStdString(socket_->readLine().toStdString());

        if (line.startsWith("Content-Length: ")) {
            length = line.split(" ")[1].toInt();
        }
        if (line == "\r\n") {
            break;
        }
    }

    rapidjson::Document payload;
    payload.Parse(socket_->read(length).data());
    rapidjson::Value* value = new rapidjson::Value(rapidjson::kObjectType);
    (*value) = payload.Move();
    Message* msg = new Message(value);
    emit messageReady(msg);
    socket_->readAll();
}