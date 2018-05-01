#ifndef ROCKET_STATE_MESSAGE_H
#define ROCKET_STATE_MESSAGE_H

#include "messages/message.hh"

class RocketStateMessage : public Message {
private:
    uint8_t state_;

public:
    RocketStateMessage(Packet packet);
    virtual ~RocketStateMessage();

    uint8_t state() const { return state_; }
    std::string stateString() const;

protected:
    virtual std::string toString();
};

#endif // ROCKET_STATE_MESSAGE