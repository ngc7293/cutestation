#include "connection/unixconnection.hh"

#include <iostream>

#include <QLocalSocket>
#include <QString>

#include "lib/rapidjson/document.h"

#include "data/data.hh"
#include "data/numericaldata.hh"
#include "distributor.hh"

UnixConnection::UnixConnection(QLocalSocket* socket)
    : Connection()
    , socket_(socket)
{
    connect(socket_, &QLocalSocket::readyRead, this, &UnixConnection::onReadyRead);
    connect(socket_, &QLocalSocket::disconnected, this, &Connection::onClose);
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
    // rapidjson::Value* value = new rapidjson::Value(rapidjson::kObjectType);
    // (*value) = payload.Move();
    Data* data = Data::fromJson(payload);
    if (data != nullptr) {
        emit dataReady(data);
    }
}