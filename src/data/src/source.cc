#include "data/source.h"

#include <string>

#include <log/log.hh>

namespace cute::data {

struct Source::Priv {
    std::string name = "";
};

Source::Source()
    : _d(*(new Priv))
{
}

Source::~Source()
{
    delete &_d;
}

void Source::close()
{
    Log::info(_d.name, "Disconnected.");
}

void Source::receiveData(std::shared_ptr<proto::Data> data)
{
    for (const proto::Measurement& measurement : data->measurements()) {
        switch (measurement.value_case()) {
            case proto::Measurement::kFloat:
                if (!publish<double>(measurement.source(), measurement.float_(), std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(measurement.timestamp())))) {
                    Log::err(_d.name) << "Could not publish type 'double' to topic '" << measurement.source() << "'" << std::endl; 
                }
                break;
            default:
                Log::warn(_d.name) << "Unhandled Measurement type" << std::endl;
        }
    }
}

void Source::receiveHandshake(std::shared_ptr<proto::Handshake> handshake)
{
    _d.name = handshake->name();
    Log::info(_d.name, "Received handshake.");

    for (const proto::Handshake_Command& command: handshake->commands()) {
        switch (command.type()) {
        case proto::Handshake_Command::FLOAT:
            if (!subscribe<double>(command.name(), [this](const auto& t, const double& v) {
                Log::info(_d.name) << "Command [double " << v << "]" << std::endl;
            })) {
                Log::warn(_d.name) << "Could not subscribe for command " << command.name() << " of type double" << std::endl;
            };
            break;
        case proto::Handshake_Command::BOOL:
            if (!subscribe<bool>(command.name(), [this](const auto& t, const bool& v) {
                Log::info(_d.name) << "Command [bool " << v << "]" << std::endl;
            })) {
                Log::warn(_d.name) << "Could not subscribe for command " << command.name() << " of type bool" << std::endl;
            };
            break;
        default:
            Log::warn(_d.name) << "Umhandled type in receiveHandshake" << std::endl;
            assert(false);
        }
    }
}

} // namespaces