#ifndef CHARTWIDGET_CONFIG_HH_
#define CHARTWIDGET_CONFIG_HH_

#include "widget_config.hh"
#include "../chartwidget.hh"

#include "lib/rapidjson/document.h"

class ChartWidget::Config : public Widget::Config {

private:
    ChartWidget* parent_;

public:
    Config(ChartWidget* parent);
    virtual ~Config();

    bool parse(rapidjson::Value& config);
    rapidjson::Value* save() const;
};

#endif // WIDGET_CONFIG_HH_