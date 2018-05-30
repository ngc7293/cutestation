#include "communication/packet.hh"

#include <iostream>

Packet::Packet()
{
    cursor_ = 5;
}

Packet::~Packet()
{
}

int Packet::length()
{
    return (data_.size() > 3 ? data_[3] : -1);
}

int Packet::id()
{
    return (data_.size() > 4 ? data_[4] : -1);
}

int Packet::validate()
{
    if (data_.size() < 6) {
        return MAYBE; // Packet metadata is at least 6 bytes
    }

    if (data_.size() < data_[3]) {
        return MAYBE;
    }

    if (data_.size() > data_[3]) {
        return CORRUPTED;
    }

    uint8_t sum = 0;
    for (uint8_t b : data_) {
        sum += b;
    }

    return (sum == 0 ? OK : CORRUPTED);
}

Packet& operator<<(Packet& Packet, uint8_t& val)
{
    Packet.data_.push_back(val);
    return Packet;
}

void Packet::checkCursor()
{
    if (cursor_ < 5) {
        cursor_ = 5;
    }
    if (cursor_ >= data_.size()) {
        cursor_ = 5;
    }
}