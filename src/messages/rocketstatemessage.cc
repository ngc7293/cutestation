#include "messages/rocketstatemessage.hh"

#include <sstream>

RocketStateMessage::RocketStateMessage(Packet packet)
    : Message(packet)
{
    packet >> state_;
}

RocketStateMessage::~RocketStateMessage()
{
}

std::string RocketStateMessage::stateString() const
{
    switch (state_) {
    case 0:
        return "INITIALISATION";
    case 1:
        return "STANDBY_ON_PAD";
    case 2:
        return "LAUNCH";
    case 3:
        return "POWERED_ASCENT";
    case 4:
        return "ENGINE_BURNOUT";
    case 5:
        return "COASTING_ASCENT";
    case 6:
        return "APOGEE_REACHED";
    case 7:
        return "DROGUE_DEPLOYMENT";
    case 8:
        return "DROGUE_DESCEND";
    case 9:
        return "MAIN_DEPLOYMENT";
    case 10:
        return "MAIN_DESCEND";
    case 11:
        return "LANDING";
    case 12:
        return "RECOVERY";
    case 13:
        return "PICKEDUP";
    }
    return "INVALID";
}

std::string RocketStateMessage::toString()
{
    std::stringstream ss;
    ss << "[STATE   " << stateString() << "]";
    return ss.str();
}