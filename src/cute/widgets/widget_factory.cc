#include <cute/widgets/widget_factory.hh>

#include <memory>

#include <QGridLayout>

#include <cute/data/average_value.hh>
#include <cute/data/dynamic_value.hh>
#include <cute/data/series_factory.hh>
#include <cute/data/series.hh>
#include <cute/data/value_factory.hh>
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
    std::string name, label, format;
    unsigned refresh_rate;

    if (!(util::json::validate("SingleValueWidget", config,
        util::json::required(name, "name"),
        util::json::optional(label, "label", "widget"),
        util::json::optional(format, "format", "%f"),
        util::json::optional(refresh_rate, "refresh_rate", 2u)
    ))) {
        return nullptr;
    }

    data::Value* ptr = nullptr;
    if (config.count("source")) {
        ptr = data::ValueFactory::build(config["source"]);
    }

    if (!ptr) {
        logging::err("SingleValueWidget") << "Missing or invalid 'source' configuration" << logging::endl;
        return nullptr;
    }

    SingleValueWidget* widget = new SingleValueWidget(parent, name);
    widget->set_value(std::unique_ptr<data::Value>(ptr));
    widget->set_label(label);
    widget->set_format(format);
    widget->start(refresh_rate);
    return widget;
}

template<>
SpacerWidget* WidgetFactory::build(const json& /*config*/, QWidget* parent)
{
    return new SpacerWidget(parent);
}


template<>
CompassWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    std::string name;
    double radius;
    unsigned int refresh_rate;
    std::vector<nlohmann::json> reference, target;

    if (!(util::json::validate("CompassWidget", config,
        util::json::required(name, "name"),
        util::json::required(radius, "radius"),
        util::json::required(reference, "reference"),
        util::json::required(target, "target"),
        util::json::optional(refresh_rate, "refresh_rate", 2u)
    ))) {
        return nullptr;
    }

    if (reference.size() != 2) {
        logging::err("CompassWidget") << "Reference configuration is not in [lat, lon] format" << logging::endl;
        return nullptr;
    }

    if (target.size() != 2) {
        logging::err("CompassWidget") << "Target configuration is not in [lat, lon] format" << logging::endl;
        return nullptr;
    }

    CompassWidget::ValuePair referenceValue = {
        std::unique_ptr<data::Value>(data::ValueFactory::build(reference[0])),
        std::unique_ptr<data::Value>(data::ValueFactory::build(reference[1]))
    };

    CompassWidget::ValuePair targetValue = {
        std::unique_ptr<data::Value>(data::ValueFactory::build(target[0])),
        std::unique_ptr<data::Value>(data::ValueFactory::build(target[1]))
    };

    CompassWidget* widget = new CompassWidget(parent, name);
    widget->set_radius(radius);
    widget->set_reference(std::move(referenceValue));
    widget->set_target(std::move(targetValue));
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