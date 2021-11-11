#include <cute/widgets/widget_factory.hh>

#include <memory>

#include <QGridLayout>

#include <cute/data/average_value.hh>
#include <cute/data/dynamic_value.hh>
#include <cute/data/series_factory.hh>
#include <cute/data/series.hh>
#include <log/log.hh>
#include <util/json.hh>
#include <util/switch.hh>

#include "button_widget.hh"
#include "chart_widget.hh"
#include "compass_widget.hh"
#include "single_value_widget.hh"
#include "spacer_widget.hh"
#include "widget_group.hh"

namespace cute::widgets {

template<>
ChartWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    ChartWidget* widget = nullptr;

    std::string name;
    unsigned length, refresh_rate;
    std::vector<int> range;
    std::vector<std::string> sources;

    if (!(util::json::validate("ChartWidget", config,
        util::json::required(name, "name"),
        util::json::required(length, "length"),
        util::json::required(range, "range"),
        util::json::required(refresh_rate, "refresh_rate"),
        util::json::required(sources, "sources")
    ) && range.size() == 2)) {
        return widget;
    }

    widget = new ChartWidget(parent, name);
    widget->set_range(std::min(range[0], range[1]), std::max(range[0], range[1]));
    widget->set_length(std::chrono::milliseconds(length));

    for (auto source: sources) {
        widget->add_series(std::make_shared<data::TimeSeries>(source, std::chrono::milliseconds(length)));
    }

    widget->start(refresh_rate);
    return widget;
}

template<>
ButtonWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    ButtonWidget* widget = nullptr;

    std::string name, command;
    unsigned refresh_rate;

    if (!(util::json::validate("ButtonWidget", config,
        util::json::required(name, "name"),
        util::json::required(command, "command"),
        util::json::required(refresh_rate, "refresh_rate")
    ))) {
        return widget;
    }

    widget = new ButtonWidget(parent, name);
    widget->set_command(command);
    widget->start(refresh_rate);

    return widget;
}

template<>
SingleValueWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    std::string name, source, strategy, format;
    unsigned refresh_rate;

    if (!(util::json::validate("SingleValueWidget", config,
        util::json::required(name, "name"),
        util::json::required(source, "source"),
        util::json::required(strategy, "strategy"),
        util::json::optional(format, "format", "%f"),
        util::json::optional(refresh_rate, "refresh_rate", 2u)
    ))) {
        return nullptr;
    }

    data::DynamicValue* ptr = nullptr;
    util::switcher::string(strategy, {
        {"min", [&] { ptr = new data::MinValue(source); }},
        {"max", [&] { ptr = new data::MaxValue(source); }},
        {"last", [&] { ptr = new data::LastValue(source); }},
        {"rolling_average", [&] {
            unsigned window;
            if (util::json::validate("SingleValueWidget", config, util::json::required(window, "window"))) {
                ptr = new data::RollingAverageValue(source, std::chrono::milliseconds(window));
            }
        }}
    }, [&] {
        logging::err("SingleValueWidget") << "Invalid strategy '" << strategy << "'" << logging::endl;
    });

    if (!ptr) {
        return nullptr;
    }

    SingleValueWidget* widget = new SingleValueWidget(parent, name);
    widget->set_value(std::unique_ptr<data::DynamicValue>(ptr));
    widget->set_format(format);
    widget->start(refresh_rate);
    return widget;
}

template<>
SpacerWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    return new SpacerWidget(parent);
}


template<>
CompassWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    std::string name;
    double radius;
    unsigned int refresh_rate;

    if (!(util::json::validate("CompassWidget", config,
        util::json::required(name, "name"),
        util::json::required(radius, "radius"),
        util::json::optional(refresh_rate, "refresh_rate", 2u)
    ))) {
        return nullptr;
    }

    CompassWidget* widget = new CompassWidget(parent, name);
    widget->set_radius(radius);
    widget->start(refresh_rate);
    return widget;
}


template<>
WidgetGroup* WidgetFactory::build(const json& config, QWidget* parent)
{
    WidgetGroup* widget = nullptr;

    std::string name;

    if (!(util::json::validate("WidgetGroup", config,
        util::json::required(name, "name")
    ))) {
        return widget;
    }

    widget = new WidgetGroup(parent, name);
    widgets::WidgetFactory::buildAll(config["widgets"], widget->grid(), widget);

    return widget;
}


template<>
Widget* WidgetFactory::build(const json& config, QWidget* parent)
{
    std::string type;

    if (!util::json::validate("Widget", config, 
        util::json::required(type, "type")
    )) {
        return nullptr;
    }

    Widget* widget = nullptr;
    util::switcher::string(type, {
        {"chart",       [&widget, config, parent]() { widget = build<ChartWidget>(config, parent); }},
        {"button",      [&widget, config, parent]() { widget = build<ButtonWidget>(config, parent); }},
        {"group",       [&widget, config, parent]() { widget = build<WidgetGroup>(config, parent); }},
        {"singlevalue", [&widget, config, parent]() { widget = build<SingleValueWidget>(config, parent); }},
        {"spacer",      [&widget, config, parent]() { widget = build<SpacerWidget>(config, parent); }},
        {"compass",     [&widget, config, parent]() { widget = build<CompassWidget>(config, parent); }}
    }, [&type]() {
        logging::err("WidgetFactory") << "Unknown widget type '" << type << "'" << logging::endl;
    });

    return widget;
}

void WidgetFactory::buildAll(const json& configs, WidgetGrid* layout, QWidget* parent)
{
    for (const json& el : configs) {
        widgets::Widget* widget = widgets::WidgetFactory::build<widgets::Widget>(el, parent);

        unsigned x = 0, y = 0, xspan = 1, yspan = 1;
        int width = -1, height= -1;

        if (widget && util::json::validate("Widget", el,
            util::json::required {x, "x"},
            util::json::required {y, "y"},
            util::json::optional {xspan, "colspan", 1u},
            util::json::optional {yspan, "rowspan", 1u},
            util::json::optional {width, "width", -1},
            util::json::optional {height, "height", -1}
        )) {
            layout->addWidget(widget, x, y, xspan, yspan);

            if (width > 0) {
                widget->setFixedWidth(width);
            }

            if (height > 0) {
                widget->setFixedHeight(height);
            }
        }
    }
}

} // namespaces