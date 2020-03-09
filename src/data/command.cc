#include "data/command.h"

#include "log.h"

namespace cute::data {

Command::Command()
    : ingestor_(nullptr)
{}

Command::~Command() {}

void Command::setIngestor(proto::DataIngestor* ingestor)
{
    if (ingestor_) {
        Log::warn("Command") << "Command alreay has an ingestor" << std::endl;
    }

    ingestor_ = ingestor;
    connect(dynamic_cast<QObject*>(this), SIGNAL(packetReady(PacketSP)), dynamic_cast<QObject*>(ingestor_), SLOT(receivePacket(PacketSP)));
}

template<>
void Command::setValue<bool>(bool value)
{
    proto::DataSP packet = std::make_shared<proto::Data>();
    // packet->set_value(value ? 1.0 : 0.0);
    // emit packetReady(packet);
}

}