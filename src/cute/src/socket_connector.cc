#include "socket_connector.h"

#include <log/log.h>
#include <packet.pb.h>

namespace cute::io {

SocketConnector::SocketConnector(QLocalSocket* socket, QThread* thread)
    : socket_(socket)
    , source_(std::make_shared<data::Source>())
{
    connect(socket_, &QLocalSocket::readyRead, this, &SocketConnector::readData);
    connect(socket_, &QLocalSocket::disconnected, this, &SocketConnector::close);
    connect(socket_, &QObject::destroyed, thread, &QThread::terminate);
}

SocketConnector::~SocketConnector()
{
    socket_->disconnect();
    source_->close();
}

void SocketConnector::readData()
{
    QByteArray buffer = socket_->readAll();
    std::shared_ptr<proto::Data> data;
    std::shared_ptr<proto::Handshake> handshake;

    proto::Packet* packet = new proto::Packet();
    if (!packet->ParseFromArray(buffer.data(), buffer.size())) {
        Log::info("Connector", "Invalid message");
        return;
    }

    switch (packet->payload_case()) {
        case proto::Packet::kHandshake:
            handshake = std::make_shared<proto::Handshake>(packet->handshake());
            source_->receiveHandshake(handshake);
            break;

        case proto::Packet::kData:
            data = std::make_shared<proto::Data>(packet->data());
            source_->receiveData(data);
            break;

        case proto::Packet::PAYLOAD_NOT_SET:
            Log::warn("SocketConnector") << "Invalid payload in Packet message" << std::endl;
    }

    delete packet;
}

void SocketConnector::close()
{
    deleteLater();
}

} // namespaces