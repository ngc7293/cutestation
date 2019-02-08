#include "widgets/config/chartwidget_config.hh"
#include "widgets/chartwidget.hh"

#include <iostream>

#include "lib/rapidjson/document.h"

ChartWidget::Config::Config(ChartWidget* parent)
    : Widget::Config(parent)
    , parent_(parent)
{
}

ChartWidget::Config::~Config()
{
}

bool ChartWidget::Config::parse(rapidjson::Value& config)
{
    if (!((Widget*) parent_)->config()->parse(config)) {
        return false;
    }

    if (config.HasMember("value")) {
        if (config["value"].IsString()) {
            parent_->value_ = config["value"].GetString();
        }
        else {
            return false;
        }
    }

    if (config.HasMember("length")) {
        if (config["length"].IsUint()) {
            parent_->graph_length_ = config["length"].GetInt();
        }
        else {

            return false;
        }
    }

    return true;
}

rapidjson::Value* ChartWidget::Config::save() const
{
    return nullptr;
}