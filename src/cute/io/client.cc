#include <cute/proto/packet.hh>
#include <log/log.hh>
#include <net/stream.hh>

#include "client.hh"

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

Client::~Client() = default;

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
                logging::warn("io::Client") << logging::tag{"client", _d->name} << "Received empty message" << logging::endl;
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

        case proto::Measurement::ValueCase::kState:
            _d->publisher.publish<int>(source, static_cast<int>(measurement.state()), timestamp);
            break;

        case proto::Measurement::ValueCase::kNumber:
            _d->publisher.publish<double>(source, measurement.number(), timestamp);
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
    logging::info("io::Client") << logging::tag{"client", _d->name} << "Received handshake" << logging::endl;

    for (const proto::Handshake::Command& command : handshake.commands()) {
        std::string name = command.name();

        auto subscribed_lambda = [this, name]<typename T>(const auto& t, const T& v) {
            proto::Packet packet;
            proto::DelimitedPacketStream stream(packet);

            logging::debug("io::Client") << logging::tag{"client", _d->name} << "Sending command " << name << logging::endl;
            proto::makeData(*packet.mutable_data(), {{
                name,
                (uint64_t) std::chrono::duration_cast<std::chrono::milliseconds>(t).count(),
                v
            }});

            *(_d->stream) << stream << std::flush;
        };

        logging::debug("io::Client") << logging::tag{"client", _d->name} << "Subscribed to " << command.name() << logging::endl;

        switch (command.type()) {
        case proto::Handshake_Command_Type::Handshake_Command_Type_BOOL:
            if (!_d->subscriber.subscribe<bool>(name, subscribed_lambda)) {
                logging::warn("io::Client") << logging::tag{"client", _d->name} << "Unable to subscribe to " << command.name() << logging::tag{"type", "bool"} << logging::endl;
            }
            break;

        case proto::Handshake_Command_Type::Handshake_Command_Type_STATE:
            if (!_d->subscriber.subscribe<int>(name, subscribed_lambda)) {
                logging::warn("io::Client") << logging::tag{"client", _d->name} << "Unable to subscribe to " << command.name() << logging::tag{"type", "int"} << logging::endl;
            }
            break;

        case proto::Handshake_Command_Type::Handshake_Command_Type_NUMBER:
            if (!_d->subscriber.subscribe<double>(name, subscribed_lambda)) {
                logging::warn("io::Client") << logging::tag{"client", _d->name} << "Unable to subscribe to " << command.name() << logging::tag{"type", "double"} << logging::endl;
            }
            break;

        case proto::Handshake_Command_Type::Handshake_Command_Type_STRING:
            if (!_d->subscriber.subscribe<std::string>(name, subscribed_lambda)) {
                logging::warn("io::Client") << logging::tag{"client", _d->name} << "Unable to subscribe to " << command.name() << logging::tag{"type", "string"} << logging::endl;
            }
            break;

        default:
            break;
        }
    }
}

}