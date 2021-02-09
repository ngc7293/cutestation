#include "io/client.hh"

#include <net/stream.hh>
#include <log/log.hh>
#include <proto/packet.hh>

namespace cute::io {

struct Client::Priv {
    std::shared_ptr<net::closeable> stream;
    std::string name;

    topic::Subscriber subscriber;
    topic::Publisher publisher;
};

Client::Client(std::shared_ptr<net::closeable> stream)
    : _d(new Priv)
{
    _d->stream = stream;
    _d->name = "unamed";
}

Client::~Client()
{
}

void Client::run()
{
    proto::Packet packet;
    proto::DelimitedPacketStream stream(packet);

    while (!(_d->stream->eof())) {
        *(_d->stream) >> stream;

        if (stream) {
            switch (packet.payload_case()) {
            case proto::Packet::PayloadCase::kData:
                onData(packet.data());
                break;

            case proto::Packet::PayloadCase::kHandshake:
                onHandshake(packet.handshake());
                break;

            default:
                Log::warn("client/" + _d->name) << "Received empty message" << std::endl;
                break;
            }
        }
    }
}

bool Client::done()
{
    return _d->stream->eof();
}

void Client::close()
{
    _d->stream->close();
}

void Client::onData(const proto::Data& data)
{
    for (const proto::Measurement& measurement: data.measurements()) {
        auto source = measurement.source();
        auto timestamp = std::chrono::duration_cast<topic::time>(std::chrono::milliseconds(measurement.timestamp()));

        switch (measurement.value_case()) {
        case proto::Measurement::ValueCase::kBool:
            _d->publisher.publish<bool>(source, measurement.bool_(), timestamp);
            break;

        case proto::Measurement::ValueCase::kInt:
            _d->publisher.publish<int>(source, measurement.int_(), timestamp);
            break;

        case proto::Measurement::ValueCase::kFloat:
            _d->publisher.publish<double>(source, measurement.float_(), timestamp);
            break;

        case proto::Measurement::ValueCase::kString:
            _d->publisher.publish<std::string>(source, measurement.string(), timestamp);
            break;

        case proto::Measurement::ValueCase::VALUE_NOT_SET:
            // Invalid data
            break;
        }
    }
}

void Client::onHandshake(const proto::Handshake& handshake)
{
    _d->name = handshake.name();
    Log::info("client/" + _d->name) << "Received handshake" << std::endl;

    for (const proto::Handshake::Command& command : handshake.commands()) {
        std::string name = command.name();

        auto subscribed_lambda = [this, name]<typename T>(const auto& t, const T& v) {
            proto::Packet packet;
            proto::DelimitedPacketStream stream(packet);

            Log::debug("client/" + _d->name) << "Sending command " << name << std::endl;
            proto::makeData(*packet.mutable_data(), {{
                name,
                (uint64_t) std::chrono::duration_cast<std::chrono::milliseconds>(t).count(),
                v
            }});

            *(_d->stream) << stream << std::flush;
        };

        Log::debug("client/" + _d->name) << "Subscribed to " << command.name() << std::endl;

        switch (command.type()) {
        case proto::Handshake_Command_Type::Handshake_Command_Type_BOOL:
            if (!_d->subscriber.subscribe<bool>(name, subscribed_lambda)) {
                Log::warn("client/" + _d->name) << "Unable to subscribe to " << command.name() << " with type bool" << std::endl;
            }
            break;

        case proto::Handshake_Command_Type::Handshake_Command_Type_INT:
            if (!_d->subscriber.subscribe<int>(name, subscribed_lambda)) {
                Log::warn("client/" + _d->name) << "Unable to subscribe to " << command.name() << " with type int" << std::endl;
            }
            break;

        case proto::Handshake_Command_Type::Handshake_Command_Type_FLOAT:
            if (!_d->subscriber.subscribe<double>(name, subscribed_lambda)) {
                Log::warn("client/" + _d->name) << "Unable to subscribe to " << command.name() << " with type double" << std::endl;
            }
            break;

        case proto::Handshake_Command_Type::Handshake_Command_Type_STRING:
            if (!_d->subscriber.subscribe<std::string>(name, subscribed_lambda)) {
                Log::warn("client/" + _d->name) << "Unable to subscribe to " << command.name() << " with type string" << std::endl;
            }
            break;

        default:
            break;
        }
    }
}

}