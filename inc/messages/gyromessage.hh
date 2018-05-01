#ifndef GYRO_MESSAGE_H
#define GYRO_MESSAGE_H

#include "messages/message.hh"

class GyroMessage : public Message {
private:
    float x_;
    float y_;
    float z_;

public:
    GyroMessage(Packet packet);
    virtual ~GyroMessage();

    float x() const { return x_; }
    float y() const { return y_; }
    float z() const { return z_; }

protected:
    virtual std::string toString();
};

#endif // GYRO_MESSAGE