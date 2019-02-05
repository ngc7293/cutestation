#ifndef MESSAGE_H
#define MESSAGE_H

#include "lib/rapidjson/document.h"

class Message {
private:
    rapidjson::Value* value_;

public:
    Message(rapidjson::Value* value);
    virtual ~Message();

    rapidjson::Value* value() { return value_; }
};

#endif // MESSAGE_H