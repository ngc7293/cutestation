#include "messages/accelerationmessage.hh"

#include <sstream>

AccelerationMessage::AccelerationMessage(Packet packet)
    : Message(packet)
{
    packet >> x_ >> y_ >> z_;
}

AccelerationMessage::~AccelerationMessage()
{
}

std::string AccelerationMessage::toString()
{
    std::stringstream ss;
    ss << "[ACCEL    " << x_ << "m/s² " << y_ << "m/s² " << z_ << "m/s² (" << norm() << "m/s²]";
    return ss.str();
}