#include "widgets/widget_factory.h"

#include <memory>

#include "log.h"

#include "data/series.h"
#include "widgets/chart_widget.h"
#include "widgets/single_value_widget.h"

namespace cute { namespace widgets {

Widget* WidgetFactory::build(data::SeriesSP& series, const json& config)
{
    Widget* widget = nullptr;

    if (config.count("type") < 1) {
        Log::err("WidgetFactory", "'type' is mandatory");
        return widget;
    }

    if (!config["type"].is_string()) {
        Log::err("WidgetFactory", "'type' expects a string");
        return widget;
    }

    std::string type = config["type"].get<std::string>();
    if (type == "chart") {
        widget = new ChartWidget(nullptr, "<name>");
    } else if (type == "single") {
        widget = new SingleValueWidget(nullptr, "<name>");
    } else {
        Log::err("WidgetFactory", "Unknown widget type '" + type + "'");
    }

    if (!widget->init(series, config)) {
        delete widget;
        return nullptr;
    }

    return widget;
}

}} // namespaces