#include "widgets/config/widget_config.hh"
#include "widgets/widget.hh"

#include "lib/rapidjson/document.h"

Widget::Config::Config(Widget* parent)
    : parent_(parent)
{
}

Widget::Config::~Config()
{
}

bool Widget::Config::parse(const rapidjson::Value& config)
{
    if (config.HasMember("name")) {
        if (config["name"].IsString()) {
            parent_->name_->setText(config["name"].GetString());
        } else {
            return false;
        }
    }

    return true;
}

rapidjson::Value* Widget::Config::save() const
{
    return nullptr;
}