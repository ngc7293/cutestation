#include "widgets/widget_factory.h"

#include <memory>

#include "log.h"
#include "util.h"

#include "data/series.h"
#include "widgets/control_widget.h"
#include "widgets/button_widget.h"
#include "widgets/chart_widget.h"
#include "widgets/single_value_widget.h"

namespace cute::widgets {

Widget* WidgetFactory::build(data::SeriesSP& series, data::CommandSP& command, const json& config)
{
    Widget* widget = nullptr;

    std::string name = "(unnamed)";
    if (has_string(config, "name")) {
        name = config["name"].get<std::string>();
    } else if (has_string(config, "source")) {
        name = config["source"].get<std::string>();
    }

    if (!has_string(config, "type")) {
        Log::err("WidgetFactory", name + ": missing or invalid mandatory configuration 'type'");
        return nullptr;
    }
    std::string type = config["type"].get<std::string>();

    if (type == "chart") {
        widget = new ChartWidget(nullptr, name);
    } else if (type == "single") {
        widget = new SingleValueWidget(nullptr, name);
    } else if (type == "button") {
        widget = new ButtonWidget(nullptr, name);
    } else {
        Log::err("WidgetFactory", name + ": unknown widget type '" + type + "'");
    }

    if (ControlWidget* cwidget = dynamic_cast<ControlWidget*>(widget)) {
        if (!cwidget->init(series, command, config)) {
            delete widget;
            return nullptr;
        }
    }
    else {
        if (!widget->init(series, config)) {
            delete widget;
            return nullptr;
        }
    }

    return widget;
}

} // namespaces