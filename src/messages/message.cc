#include "messages/message.hh"

#include "lib/rapidjson/ostreamwrapper.h"
#include "lib/rapidjson/prettywriter.h"

Message::Message(rapidjson::Value* value)
    : value_(value)
{
}

Message::~Message()
{
    delete value_;
}