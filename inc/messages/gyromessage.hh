#ifndef GYRO_MESSAGE_H
#define GYRO_MESSAGE_H

#include "messages/message.hh"

class GyroMessage : public Message {
private:
    float q1_;
    float q2_;
    float q3_;
    float q4_;

public:
    GyroMessage(Packet packet);
    virtual ~GyroMessage();

    float q1() const { return q1_; }
    float q2() const { return q2_; }
    float q3() const { return q3_; }
    float q4() const { return q4_; }

protected:
    virtual std::string toString();
};

#endif // GYRO_MESSAGE