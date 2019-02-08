#include "widgets/config/widget_config.hh"
#include "widgets/widget.hh"

#include <iostream>

#include "lib/rapidjson/document.h"

Widget::Config::Config(Widget* parent)
    : parent_(parent)
{
}

Widget::Config::~Config()
{
}

bool Widget::Config::parse(rapidjson::Value& config)
{
    if (config.HasMember("name")) {
        if (config["name"].IsString()) {
            parent_->name_->setText(config["name"].GetString());
        }
        else {
            std::cout << "no name" << std::endl;
            return false;
        }
    }

    return true;
}

rapidjson::Value* Widget::Config::save() const
{
    return nullptr;
}