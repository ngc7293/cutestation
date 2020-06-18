#ifndef CUTE_PROTO_PACKET_H_
#define CUTE_PROTO_PACKET_H_

#include <packet.pb.h>

#include "delimited_protobuf_stream.h"

namespace cute::proto {

typedef DelimitedProtobufStream<Packet> DelimitedPacketStream;

}

#endif