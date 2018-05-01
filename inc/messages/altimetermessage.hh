#ifndef ALTIMETER_MESSAGE_H
#define ALTIMETER_MESSAGE_H

#include "messages/message.hh"

class AltimeterMessage : public Message {
private:
    float agl_altitude_;
    float altitude_;
    float velocity_;
    float acceleration_;

public:
    AltimeterMessage(Packet packet);
    virtual ~AltimeterMessage();

    float agl_altitude() const { return agl_altitude_; }
    float altitude() const { return altitude_; }
    float velocity() const { return velocity_; }
    float acceleration() const { return acceleration_; }

protected:
    virtual std::string toString();
};

#endif // ALTIMETER_MESSAGE_H