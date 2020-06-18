#include "io/client.h"

#include <log/log.h>
#include <proto/packet.h>

namespace cute::io {

struct Client::Priv {
    std::shared_ptr<net::socket> ios;
    std::string name;
};

Client::Client(std::shared_ptr<net::socket> ios)
    : _d(new Priv)
{
    _d->ios = ios;
    _d->name = "client/unamed";
}

Client::~Client()
{
    _d->ios->close();
}

void Client::run()
{
    proto::Packet packet;
    proto::DelimitedProtobufStream<proto::Packet> stream(packet);

    while (!(_d->ios->eof())) {
        std::istream& is = *(_d->ios);
        is >> stream;

        if (stream) {
            Log::info(_d->name) << "Received message [handshake=" << packet.has_handshake() << "] [data=" << packet.has_data() << "]" << std::endl;
            
            switch (packet.payload_case()) {
            case proto::Packet::PayloadCase::kData:
                Log::info(_d->name) << "Received data" << std::endl;
                break;

            case proto::Packet::PayloadCase::kHandshake:
                _d->name = "client/" + packet.handshake().name();
                Log::info(_d->name) << "Received handshake" << std::endl;
                break;

            default:
                Log::warn(_d->name) << "Received empty message" << std::endl;
                break;
            }        
        }
    }
}

}