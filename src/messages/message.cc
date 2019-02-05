#include "messages/message.hh"

Message::Message(rapidjson::Value* value)
    : value_(value)
{
}

Message::~Message()
{
}