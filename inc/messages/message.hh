#ifndef MESSAGE_HH_
#define MESSAGE_HH_

#include "lib/rapidjson/document.h"

class Message {
private:
    rapidjson::Value* value_;

public:
    Message(rapidjson::Value* value);
    virtual ~Message();

    rapidjson::Value& value() { return *value_; }
};

#endif // MESSAGE_HH_