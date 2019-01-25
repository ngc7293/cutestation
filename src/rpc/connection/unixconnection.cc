#include "rpc/connection/unixconnection.hh"

#include <iostream>

#include <QLocalSocket>
#include <QString>

UnixConnection::UnixConnection(QLocalSocket* socket)
    : Connection()
    , socket_(socket)
{
    connect(socket_, &QLocalSocket::readyRead, this, &UnixConnection::onReadyRead);
    connect(socket_, &QLocalSocket::disconnected, this, &UnixConnection::deleteLater);
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

    std::cout << "UnixConnection at " << this << " with length " << length << std::endl;
    std::cout << socket_->read(length).toStdString() << std::endl;
    socket_->readAll();
}