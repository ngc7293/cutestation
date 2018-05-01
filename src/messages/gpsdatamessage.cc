#include "messages/gpsdatamessage.hh"

#include <sstream>

GPSDataMessage::GPSDataMessage(Packet packet)
    : Message(packet)
{
    packet >> lon_ >> lat_ >> altitude_;
}

GPSDataMessage::~GPSDataMessage()
{
}

std::string GPSDataMessage::toString()
{
    std::stringstream ss;
    ss << "[GPS DATA " << lon_ << "° " << lat_ << "° " << altitude_ << "m]";
    return ss.str();
}