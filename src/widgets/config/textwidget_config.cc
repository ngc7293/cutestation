#include "widgets/config/widget_config.hh"
#include "widgets/textwidget.hh"

#include "lib/rapidjson/document.h"

template <>
bool Widget::Config<TextWidget>::parse(const rapidjson::Value& config)
{
    if (!((Widget*)parent_)->config()->parse(config)) {
        return false;
    }

    JSON_GET_OR_DIE(config, value, setValue, String);
    JSON_GET_OR_DIE(config, display_type, setDisplayType, String);

    return true;
}

template class Widget::Config<TextWidget>;