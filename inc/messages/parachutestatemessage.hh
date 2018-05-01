#ifndef PARACHUTE_STATE_MESSAGE_H
#define PARACHUTE_STATE_MESSAGE_H

#include "messages/message.hh"

class ParachuteStateMessage : public Message {
private:
    bool main_detect_;
    bool main_fired_;
    bool drogue_detect_;
    bool drogue_fired_;

public:
    ParachuteStateMessage(Packet packet);
    virtual ~ParachuteStateMessage();

    bool main_detect() const { return main_detect_; }
    bool main_fired() const { return main_fired_; }
    bool drogue_detect() const { return drogue_detect_; }
    bool drogue_fired() const { return drogue_fired_; }

protected:
    virtual std::string toString();
};

#endif // PARACHUTE_STATE_MESSAGE