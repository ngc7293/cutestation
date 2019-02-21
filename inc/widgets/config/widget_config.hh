#ifndef WIDGET_CONFIG_HH_
#define WIDGET_CONFIG_HH_

#include "../widget.hh"

#include "lib/rapidjson/document.h"

class Widget::Config {

private:
    Widget* parent_;

public:
    Config(Widget* parent);
    virtual ~Config();

    bool parse(const rapidjson::Value& config);
    rapidjson::Value* save() const;
};

#define JSON_GET_OR_DIE(json, name, member, type)         \
    if (json.HasMember(#name)) {                          \
        if (json[#name].Is##type()) {                     \
            parent_->member##_ = json[#name].Get##type(); \
        } else {                                          \
            return false;                                 \
        }                                                 \
    }

#endif // WIDGET_CONFIG_HH_