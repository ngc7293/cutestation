#include "io/socket_connector.h"

#include "log.h"
#include "proto/packet.h"


namespace cute::io {

SocketConnector::SocketConnector(QLocalSocket* socket, QThread* thread)
    : socket_(socket)
    , source_(std::make_shared<data::Source>())
{
    connect(socket_, &QLocalSocket::readyRead, this, &SocketConnector::readData);
    connect(socket_, &QLocalSocket::disconnected, this, &SocketConnector::close);
    connect(socket_, &QObject::destroyed, thread, &QThread::terminate);

    connect(source_.get(), &data::Source::dataReady, this, &SocketConnector::receiveData);
    readData();
}

SocketConnector::~SocketConnector()
{
    socket_->disconnect();
    source_->close();
}

void SocketConnector::readData()
{
    QByteArray buffer = socket_->readAll();
    proto::DataSP data;
    proto::HandshakeSP handshake;

    proto::Packet* packet = new proto::Packet();
    if (!packet->ParseFromArray(buffer.data(), buffer.size())) {
        Log::info("Connector", "Invalid message");
        return;
    }

    switch (packet->payload_case()) {
        case proto::Packet::kHandshake:
            handshake = std::make_shared<proto::Handshake>(packet->handshake());
            source_->receiveHandshake(handshake);
            // emit handshakeReady(handshake);
            break;

        case proto::Packet::kData:
            data = std::make_shared<proto::Data>(packet->data());
            source_->receiveData(data);
            // emit dataReady(data);
            break;

        case proto::Packet::PAYLOAD_NOT_SET:
            Log::warn("SocketConnector") << "Invalid payload in Packet message" << std::endl;
    }

    delete packet;
}

void SocketConnector::receiveData(proto::DataSP data)
{
    QByteArray buffer;
    proto::Packet* packet = new proto::Packet();
    packet->set_allocated_data(data.get());

    buffer.resize(packet->ByteSizeLong());

    packet->SerializeToArray(buffer.data(), buffer.size());
    socket_->write(buffer, buffer.size());
    packet->release_data();
}

void SocketConnector::close()
{
    deleteLater();
}

} // namespaces