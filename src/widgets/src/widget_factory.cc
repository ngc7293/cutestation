#include "widgets/widget_factory.hh"

#include <memory>

#include <log/log.hh>
#include <util/json.hh>
#include <data/series.hh>
#include <data/series_factory.hh>

#include "widgets/control_widget.hh"
#include "widgets/button_widget.hh"
#include "widgets/chart_widget.hh"
#include "widgets/single_value_widget.hh"

namespace cute::widgets {

template<>
ChartWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    ChartWidget* widget = nullptr;

    std::string name;
    unsigned length;
    std::vector<int> range;

    std::shared_ptr<data::TimeSeries<double>> series = data::SeriesFactory::build<data::TimeSeries<double>>(config);
    if (!series) {
        return widget;
    }

    if (!(util::json::validate("ChartWidget", config,
        util::json::required(name, "name"),
        util::json::required(length, "length"),
        util::json::required(range, "range")
    ) && range.size() == 2)) {
        return widget;
    }

    widget = new ChartWidget(parent, name);
    widget->set_series(series);
    widget->set_range(std::min(range[0], range[1]), std::max(range[0], range[1]));
    widget->set_length(length);
    return widget;
}

template<>
SingleValueWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    return nullptr;
}

template<>
ButtonWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    return nullptr;
}

template<>
Widget* WidgetFactory::build(const json& config, QWidget* parent)
{
    Widget* widget = nullptr;

    std::string type;
    unsigned refresh_rate;

    if (!util::json::validate("Widget", config, 
        util::json::required(type, "type"),
        util::json::required(refresh_rate, "refresh_rate")
    )) {
        return widget;
    }

    if (type == "chart") {
        widget = build<ChartWidget>(config, parent);
    } else if (type == "single") {
        widget = build<SingleValueWidget>(config, parent);
    } else if (type == "button") {
        widget = build<ButtonWidget>(config, parent);
    } else {
        Log::err("WidgetFactory", "Unknown widget type '" + type + "'");
        return widget;
    }

    if (widget) {
        widget->start(refresh_rate);
    }

    return widget;
}

} // namespaces