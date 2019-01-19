#include "connector/unixconnector.hh"

#include <iostream>

#include <QLocalSocket>
#include <QString>


UnixConnector::UnixConnector(QLocalSocket* socket)
    : socket_(socket)
{
    connect(socket_, &QLocalSocket::readyRead, this, &UnixConnector::onReadyRead);
}

UnixConnector::~UnixConnector()
{
    socket_->disconnectFromServer();
    delete socket_;
}

void UnixConnector::onReadyRead()
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

    std::cout << "UnixConnector at " << this << " with length " << length << std::endl;
    std::cout << socket_->read(length).toStdString() << std::endl;
    socket_->readAll();
}