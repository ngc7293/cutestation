#include "data/command.h"

#include "log.h"
#include "util.h"

namespace cute::data {

Command::Command(std::string name)
    : name_(name)
{}

Command::~Command() {}

void Command::registerDataSource(const SourceSP& source)
{
    sources_.push_back(source);
}

void Command::unregisterDataSource(const SourceSP& source)
{
    for (auto it = sources_.begin(); it != sources_.end(); it++) {
        if (*it == source) {
            sources_.erase(it);
            return;
        }
    }
}

template<>
void Command::setValue<bool>(bool value)
{
    proto::DataSP data = std::make_shared<proto::Data>();
    proto::Measurement* measurement = data->add_measurements();

    measurement->set_source(name_);
    measurement->set_timestamp(now());
    measurement->set_bool_(value);

    for (SourceSP& source : sources_) {
        source->sendData(data);
    }
}

}