#include "messages/message.hh"

#include <iostream>

#include "lib/rapidjson/ostreamwrapper.h"
#include "lib/rapidjson/prettywriter.h"

Message::Message(rapidjson::Value* value)
    : value_(value)
{
    rapidjson::OStreamWrapper osw(std::cout);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    value_->Accept(writer);
}

Message::~Message()
{
    delete value_;
}