#include "messages/altimetermessage.hh"

#include <sstream>

AltimeterMessage::AltimeterMessage()
    : Message()
{
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