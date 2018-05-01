#include "messages/ejectionsettingsmessage.hh"

#include <sstream>

EjectionSettingsMessage::EjectionSettingsMessage(Packet packet)
    : Message(packet)
{
    packet >> ejection_delay_ >> ultrasonic_delay_ >> ejection_altitude_;
}

EjectionSettingsMessage::~EjectionSettingsMessage()
{
}

std::string EjectionSettingsMessage::toString()
{
    std::stringstream ss;
    ss << "[EJECTION " << ejection_delay_ << "ms " << ultrasonic_delay_ << "ms " << ejection_altitude_ << "m]";
    return ss.str();
}