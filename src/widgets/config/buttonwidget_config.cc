#include "widgets/buttonwidget.hh"
#include "widgets/config/widget_config.hh"

#include "lib/rapidjson/document.h"

template <>
bool Widget::Config<ButtonWidget>::parse(const rapidjson::Value& config)
{
    if (!((Widget*)parent_)->config()->parse(config)) {
        return false;
    }

    JSON_GET_OR_DIE(config, text, setText, String);
    JSON_GET_OR_DIE(config, board, setBoard, Int);
    JSON_GET_OR_DIE(config, message, setMessage, Int);
    JSON_GET_OR_DIE(config, value, setMessage, Int);

    return true;
}

template class Widget::Config<ButtonWidget>;