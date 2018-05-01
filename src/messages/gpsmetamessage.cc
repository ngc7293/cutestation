#include "messages/gpsmetamessage.hh"

#include <sstream>

GPSMetaMessage::GPSMetaMessage(Packet packet)
    : Message(packet)
{
    packet >> fix_ >> count_;
}

GPSMetaMessage::~GPSMetaMessage()
{
}

std::string GPSMetaMessage::fixString() const
{
    switch (fix_) {
    case 0:
        return "No Fix";
    case 1:
        return "Dead Reckoning only";
    case 2:
        return "2D-Fix";
    case 3:
        return "3D-Fix";
    case 4:
        return "GPS + dead reckoning combined";
    case 5:
        return "Time only fix";
    }
    return "Invalid";
}

std::string GPSMetaMessage::toString()
{
    std::stringstream ss;
    ss << "[GPS DATA " << fixString() << ", " << count_ << "satellite" << (count_ == 1 ? "s" : "" ) << "]";
    return ss.str();
}