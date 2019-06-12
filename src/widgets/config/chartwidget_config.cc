#include "widgets/chartwidget.hh"
#include "widgets/config/widget_config.hh"

#include "lib/rapidjson/document.h"

template <>
bool Widget::Config<ChartWidget>::parse(const rapidjson::Value& config)
{
    if (!((Widget*)parent_)->config()->parse(config)) {
        return false;
    }

    JSON_GET_OR_DIE(config, value, setValue, String);
    JSON_GET_OR_DIE(config, length, setGraphLength, Uint);
    JSON_GET_OR_DIE(config, always_update, setAlwaysUpdate, Bool);

    return true;
}

template class Widget::Config<ChartWidget>;