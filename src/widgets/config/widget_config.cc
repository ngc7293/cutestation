#include "widgets/config/widget_config.hh"
#include "widgets/widget.hh"

#include "lib/rapidjson/document.h"

template <>
bool Widget::Config<Widget>::parse(const rapidjson::Value& config)
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

template <class T>
rapidjson::Value* Widget::Config<T>::save() const
{
    return nullptr;
}

template class Widget::Config<Widget>;