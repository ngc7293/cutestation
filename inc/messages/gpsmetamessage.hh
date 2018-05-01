#ifndef GPS_META_MESSAGE_H
#define GPS_META_MESSAGE_H

#include "messages/message.hh"

class GPSMetaMessage : public Message {
private:
    uint8_t fix_;
    uint8_t count_;

public:
    GPSMetaMessage(Packet packet);
    virtual ~GPSMetaMessage();

    uint8_t fix() const { return fix_; }
    uint8_t count() const { return count_; }

    std::string fixString() const;

protected:
    virtual std::string toString();
};

#endif // GPS_META_MESSAGE