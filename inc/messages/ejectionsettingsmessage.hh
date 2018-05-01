#ifndef EJECTION_SETTINGS_MESSAGE_H
#define EJECTION_SETTINGS_MESSAGE_H

#include "messages/message.hh"

class EjectionSettingsMessage : public Message {
private:
    float ejection_delay_;
    float ultrasonic_delay_;
    float ejection_altitude_;

public:
    EjectionSettingsMessage(Packet packet);
    virtual ~EjectionSettingsMessage();

    float ejection_delay() const { return ejection_delay_; }
    float ultrasonic_delay() const { return ultrasonic_delay_; }
    float ejection_altitude() const { return ejection_altitude_; }

protected:
    virtual std::string toString();
};

#endif // EJECTION_SETTINGS_MESSAGE