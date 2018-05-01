#include "messages/altimetermessage.hh"

#include <sstream>

AltimeterMessage::AltimeterMessage(Packet packet)
    : Message(packet)
{
    packet >> agl_altitude_ >> altitude_ >> velocity_ >> acceleration_;
}

AltimeterMessage::~AltimeterMessage()
{
}

std::string AltimeterMessage::toString()
{
    std::stringstream ss;
    ss << "[ALTIMETER " << agl_altitude_ << "m AGL " << altitude_ << "m " << velocity_ << "m/s " << acceleration_ << "m/s²]";
    return ss.str();
}