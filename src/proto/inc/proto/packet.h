#ifndef CUTE_PROTO_PACKET_H_
#define CUTE_PROTO_PACKET_H_

#include <any>

#include <packet.pb.h>

#include "delimited_protobuf_stream.h"

namespace cute::proto {

struct _measurement_initializer {
    const std::string& s;
    const uint64_t t;
    const std::any v;

    _measurement_initializer(const std::string& s, const uint64_t t, const std::any v)
        : s(s)
        , t(t)
        , v(v)
    {
    }
};

struct _command_initializer {
    const std::string& n;
    const std::type_info& t;

    _command_initializer(const std::string& n, const std::type_info& t)
        : n(n)
        , t(t)
    {
    }
};

void makeData(proto::Data& data, std::initializer_list<_measurement_initializer> list);
void makeHandshake(proto::Handshake& handshake, const std::string& name, std::initializer_list<_command_initializer> list);

typedef DelimitedProtobufStream<Packet> DelimitedPacketStream;

}

#endif