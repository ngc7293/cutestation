#include "data/source.h"

#include <string>

#include <log/log.h>

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
}

} // namespaces