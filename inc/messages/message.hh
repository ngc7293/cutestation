#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

#include "communication/packet.hh"

class Message {
public:
    static Message* fromPacket(Packet& packet);

protected:
    Packet data_;

public:
    Message(Packet packet);
    virtual ~Message();

    int id() { return data_.id(); }

    Packet& packet() { return data_; }

    friend std::ostream& operator<<(std::ostream& stream, Message& message);
    friend std::ostream& operator<<(std::ostream& stream, Message* message);

protected:
    virtual std::string toString() = 0;
};

#endif // MESSAGE_H