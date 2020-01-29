#include "widgets/widget_factory.h"

#include <memory>

#include "log.h"

#include "data/series.h"
#include "widgets/chart_widget.h"

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

    if (config["type"].get<std::string>() == "chart") {
        widget = new ChartWidget(nullptr, "<name>");
    }

    if (!widget || !widget->init(series, config)) {
        return nullptr;
    }

    return widget;
}

}} // namespaces