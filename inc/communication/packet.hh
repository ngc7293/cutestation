#ifndef PACKET_H
#define PACKET_H

#include <vector>

#include <cstdint>
#include <cstring>

class Packet {
public:
    static const int CORRUPTED = 0;
    static const int MAYBE = 1;
    static const int OK = 2;

private:
    std::vector<uint8_t> data_;
    unsigned int cursor_;

public:
    Packet();
    ~Packet();

    int length();
    int id();
    int validate(); // 0: corrupted, 1: maybe, 2: ok

    // Operator Overloading
    friend Packet& operator<<(Packet& packet, uint8_t& val);

    template<typename T>
    friend Packet& operator>>(Packet& packet, T& val);
    
    // Simple setters
    void setCursor(unsigned int pos) { cursor_ = pos; }

    // Getters
    std::vector<uint8_t>& data() { return data_; }
    unsigned int cursor() const { return cursor_; }

private:
    void checkCursor();
};

template<typename T>
Packet& operator>>(Packet& packet, T& val)
{
    packet.checkCursor();
    memcpy(&val, packet.data_.data() + packet.cursor_, sizeof(T));
    packet.cursor_ += sizeof(T);
    return packet;
}

#endif // PACKET_H