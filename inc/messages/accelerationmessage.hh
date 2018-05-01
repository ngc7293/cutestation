#ifndef ACCELERATION_MESSAGE_H
#define ACCELERATION_MESSAGE_H

#include "messages/message.hh"

#include <cmath>

class AccelerationMessage : public Message {
private:
    float x_;
    float y_;
    float z_;

public:
    AccelerationMessage(Packet packet);
    virtual ~AccelerationMessage();

    float x() const { return x_; }
    float y() const { return y_; }
    float z() const { return z_; }
    float norm() const { 
        return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

protected:
    virtual std::string toString();
};

#endif // ACCELERATION_MESSAGE