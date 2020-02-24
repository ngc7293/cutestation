#ifndef PROTO_PACKET_H_
#define PROTO_PACKET_H_

#include <memory>

#include <QObject>
#include <QMetaType>

#include "packet.pb.h"

typedef std::shared_ptr<Packet> PacketSP;
Q_DECLARE_METATYPE(PacketSP)

class PacketIngestor {
public slots:
    virtual void receivePacket(PacketSP packet) = 0;
};

Q_DECLARE_INTERFACE(PacketIngestor, "cute.proto.PacketIngestor")

class PacketEmitter {
public:
    ~PacketEmitter() { }
signals:
    virtual void packetReady(PacketSP packet) = 0;
};

Q_DECLARE_INTERFACE(PacketEmitter, "cute.proto.PacketEmitter")

#endif