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

bool ChartWidget::Config::parse(const rapidjson::Value& config)
{
    if (!((Widget*)parent_)->config()->parse(config)) {
        return false;
    }

    JSON_GET_OR_DIE(config, value, value, String);
    JSON_GET_OR_DIE(config, length, graph_length, Uint);
    JSON_GET_OR_DIE(config, always_update, always_update, Bool);

    return true;
}

rapidjson::Value* ChartWidget::Config::save() const
{
    return nullptr;
}