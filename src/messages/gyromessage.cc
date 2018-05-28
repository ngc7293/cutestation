#include "messages/gyromessage.hh"

#include <sstream>

GyroMessage::GyroMessage(Packet packet)
    : Message(packet)
{
    packet >> q1_ >> q2_ >> q3_ >> q4_;
}

GyroMessage::~GyroMessage()
{
}

std::string GyroMessage::toString()
{
    std::stringstream ss;
    ss << "[GYRO   " << q1_ << "° " << q2_ << "° " << q3_ << "° " << q4_ << "° QUATERNIONS]";
    return ss.str();
}