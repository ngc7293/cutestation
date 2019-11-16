#ifndef PROTO_PACKET_H_
#define PROTO_PACKET_H_

#include <memory>

#include <QMetaType>

#include "packet.pb.h"

typedef std::shared_ptr<Packet> PacketSP;
Q_DECLARE_METATYPE(PacketSP);

#endif