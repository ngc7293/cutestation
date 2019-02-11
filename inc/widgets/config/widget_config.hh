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

#endif // WIDGET_CONFIG_HH_