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
#include "number_value_widget.hh"
#include "spacer_widget.hh"
#include "state_value_widget.hh"
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
NumberValueWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    std::string name, label, format;
    unsigned refresh_rate;

    if (!(util::json::validate("NumberValueWidget", config,
        util::json::required(name, "name"),
        util::json::optional(label, "label", "widget"),
        util::json::optional(format, "format", "%f"),
        util::json::optional(refresh_rate, "refresh_rate", 2u)
    ))) {
        return nullptr;
    }

    data::NumberValue* ptr = nullptr;
    if (config.count("source")) {
        ptr = data::ValueFactory::build<double>(config["source"]);
    }

    if (!ptr) {
        logging::err("NumberValueWidget") << "Missing or invalid 'source' configuration" << logging::endl;
        return nullptr;
    }

    NumberValueWidget* widget = new NumberValueWidget(parent, name);
    widget->set_value(std::unique_ptr<data::NumberValue>(ptr));
    widget->set_label(label);
    widget->set_format(format);
    widget->start(refresh_rate);
    return widget;
}

std::optional<StateRangeMapping> buildStateRangeMapping(const std::string& key, const json& value)
{
    StateRangeMapping mapping;

    try {
        auto pos = key.find("~");

        if (pos == std::string::npos) {
            mapping.a = std::stol(key);
            mapping.b = mapping.a;
        } else {
            if (pos == 0) {
                mapping.a = std::numeric_limits<int>::min();
            } else {
                mapping.a = std::stol(key.substr(0, pos));
            }

            if (pos == key.length() - 1) {
                mapping.b = std::numeric_limits<int>::max();
            } else {
                mapping.b = std::stol(key.substr(pos + 1, key.length()));
            }
        }
    } catch (...) {
        logging::err("StateRangeMapping") << "Could not parse range key '" << key << "'" << logging::endl;
        return {};
    }

    if (value.is_object()) {
        if (!(util::json::validate("StateRangeMapping", value,
            util::json::required(mapping.display, "display"),
            util::json::optional(mapping.color, "color", ""),
            util::json::optional(mapping.backgroundColor, "background", "")
        ))) {
            return {};
        }
    } else if (value.is_string()) {
        mapping.display = value.get<std::string>();
    } else {
        logging::err("StateRangeMapping") << "Invalid JSON type for mapping element" << logging::endl;
        return {};
    }

    return {std::move(mapping)};
}

std::vector<StateRangeMapping> buildStateRangeMappings(const json& config)
{
    std::vector<StateRangeMapping> mappings;

    for (const auto& [key, value]: config.items()) {
        auto maybe = buildStateRangeMapping(key, value);

        if (maybe) {
            mappings.emplace_back(maybe.value());
        }
    }

    for (const auto& m: mappings) {
        logging::debug("StateRangeMapping") << logging::tag{"a", m.a} << logging::tag{"b", m.b} << logging::tag{"display", m.display} << logging::tag{"color", m.color} << logging::tag{"background", m.backgroundColor} << logging::endl;
    }

    return mappings;
}

template<>
StateValueWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    std::string name, label, format;
    unsigned refresh_rate;

    if (!(util::json::validate("StateValueWidget", config,
        util::json::required(name, "name"),
        util::json::optional(label, "label", "widget"),
        util::json::optional(refresh_rate, "refresh_rate", 2u)
    ))) {
        return nullptr;
    }

    data::StateValue* ptr = nullptr;
    if (config.count("source")) {
        ptr = data::ValueFactory::build<int>(config["source"]);
    }

    std::vector<StateRangeMapping> mappings;
    if (config.count("mapping") && config["mapping"].is_object()) {
        mappings = buildStateRangeMappings(config["mapping"]);
    } else {
        logging::warn("StateValueWidget") << "No mapping configured, displaying raw value";
    }

    if (!ptr) {
        logging::err("StateValueWidget") << "Missing or invalid 'source' configuration" << logging::endl;
        return nullptr;
    }

    StateValueWidget* widget = new StateValueWidget(parent, name);
    widget->set_value(std::unique_ptr<data::StateValue>(ptr));
    widget->set_value_mapping(std::move(mappings));
    widget->set_label(label);
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
        std::unique_ptr<data::NumberValue>(data::ValueFactory::build<double>(reference[0])),
        std::unique_ptr<data::NumberValue>(data::ValueFactory::build<double>(reference[1]))
    };

    CompassWidget::ValuePair targetValue = {
        std::unique_ptr<data::NumberValue>(data::ValueFactory::build<double>(target[0])),
        std::unique_ptr<data::NumberValue>(data::ValueFactory::build<double>(target[1]))
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
        {"numbervalue", [&widget, config, parent]() { widget = build<NumberValueWidget>(config, parent); }},
        {"statevalue",  [&widget, config, parent]() { widget = build<StateValueWidget>(config, parent); }},
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