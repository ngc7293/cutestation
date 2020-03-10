#include "data/command.h"

#include "log.h"
#include "util.h"

namespace cute::data {

Command::Command(std::string name)
    : name_(name)
{}

Command::~Command() {}

void Command::registerDataSource(Source* source)
{
    sources_.push_back(source);
}

template<>
void Command::setValue<bool>(bool value)
{
    proto::DataSP data = std::make_shared<proto::Data>();
    proto::Measurement* measurement = data->add_measurements();

    measurement->set_source(name_);
    measurement->set_timestamp(now());
    measurement->set_bool_(value);

    for (Source* source : sources_) {
        source->sendData(data);
    }
}

}