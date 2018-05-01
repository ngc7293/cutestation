#ifndef GPS_DATA_MESSAGE_H
#define GPS_DATA_MESSAGE_H

#include "messages/message.hh"

class GPSDataMessage : public Message {
private:
    float lon_;
    float lat_;
    uint32_t altitude_;

public:
    GPSDataMessage(Packet packet);
    virtual ~GPSDataMessage();

    float lon() const { return lon_; }
    float lat() const { return lat_; }
    uint32_t altitude() const { return altitude_; }

protected:
    virtual std::string toString();
};

#endif // GPS_DATA_MESSAGE