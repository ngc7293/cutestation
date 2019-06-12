#ifndef WIDGET_CONFIG_HH_
#define WIDGET_CONFIG_HH_

#include "../widget.hh"

#include "lib/rapidjson/document.h"

template <class T>
class Widget::Config {

private:
    T* parent_;

public:
    Config(T* parent)
    {
        parent_ = parent;
    }

    bool parse(const rapidjson::Value& config);
    rapidjson::Value* save() const;
};

#define JSON_GET_OR_DIE(json, name, setter, type)     \
    if (json.HasMember(#name)) {                      \
        if (json[#name].Is##type()) {                 \
            parent_->setter(json[#name].Get##type()); \
        } else {                                      \
            return false;                             \
        }                                             \
    }

#endif // WIDGET_CONFIG_HH_