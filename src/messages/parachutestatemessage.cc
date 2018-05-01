#include "messages/parachutestatemessage.hh"

#include <sstream>

ParachuteStateMessage::ParachuteStateMessage(Packet packet)
    : Message(packet)
{
    uint8_t main_mask;
    uint8_t drogue_mask;
    packet >> main_mask >> drogue_mask;

    main_detect_ = (main_mask & 0b00010000);
    main_fired_ = (main_mask & 0b00000001);
    drogue_detect_ = (drogue_mask & 0b00010000);
    drogue_fired_ = (drogue_mask & 0b00000001);
}

ParachuteStateMessage::~ParachuteStateMessage()
{
}

std::string ParachuteStateMessage::toString()
{
    std::stringstream ss;
    ss << "[CHUTE   ";
    
    ss << " MAIN:";
    if (main_fired_) {
        ss << "FIRED";
    } else if (main_detect_) {
        ss << "DETECTED";
    } else {
        ss << "NONE";
    }

    ss << " DROGUE:";
    if (drogue_fired_) {
        ss << "FIRED";
    } else if (drogue_detect_) {
        ss << "DETECTED";
    } else {
        ss << "NONE";
    }

    ss << "]";
    return ss.str();
}