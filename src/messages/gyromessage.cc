#include "messages/gyromessage.hh"

#include <sstream>

GyroMessage::GyroMessage(Packet packet)
    : Message(packet)
{
    packet >> x_ >> y_ >> z_;
}

GyroMessage::~GyroMessage()
{
}

std::string GyroMessage::toString()
{
    std::stringstream ss;
    ss << "[GYRO   " << x_ << "° " << y_ << "° " << z_ << "° EULER]";
    return ss.str();
}