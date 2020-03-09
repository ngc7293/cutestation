#include "socket/socket_connector.h"

#include "log.h"
#include "proto/packet.h"


namespace cute::io {

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
    QByteArray buffer = socket_->readAll();
    proto::DataSP data;

    proto::Packet* packet = new proto::Packet();
    packet->ParseFromArray(buffer.data(), buffer.size());

    switch (packet->payload_case()) {
        case proto::Packet::kData:
            data = std::make_shared<proto::Data>(packet->data());
            emit dataReady(data);
            break;
        case proto::Packet::kHandshake:
            break;

        case proto::Packet::PAYLOAD_NOT_SET:
            Log::info("SocketConnector") << "Invalid payload in Packet message" << std::endl;
    }

    delete packet;
}

void SocketConnector::close()
{
    deleteLater();
}

} // namespaces