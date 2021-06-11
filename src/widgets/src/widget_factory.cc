#include "widgets/widget_factory.hh"

#include <memory>

#include <QGridLayout>

#include <log/log.hh>
#include <util/json.hh>
#include <util/switch.hh>
#include <data/series.hh>
#include <data/series_factory.hh>

#include "widgets/button_widget.hh"
#include "widgets/chart_widget.hh"
#include "widgets/widget_group.hh"

namespace cute::widgets {

template<>
ChartWidget* WidgetFactory::build(const json& config, QWidget* parent)
{
    ChartWidget* widget = nullptr;

    std::string name;
    unsigned length, refresh_rate;
    std::vector<int> range;

    std::shared_ptr<data::TimeSeries<double>> series = data::SeriesFactory::build<data::TimeSeries<double>>(config);
    if (!series) {
        return widget;
    }

    if (!(util::json::validate("ChartWidget", config,
        util::json::required(name, "name"),
        util::json::required(length, "length"),
        util::json::required(range, "range"),
        util::json::required(refresh_rate, "refresh_rate")
    ) && range.size() == 2)) {
        return widget;
    }

    widget = new ChartWidget(parent, name);
    widget->set_series(series);
    widget->set_range(std::min(range[0], range[1]), std::max(range[0], range[1]));
    widget->set_length(length);
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
WidgetGroup* WidgetFactory::build(const json& config, QWidget* parent)
{
    WidgetGroup* widget = nullptr;

    std::string name, command;

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
    Widget* widget = nullptr;

    std::string type;

    if (!util::json::validate("Widget", config, 
        util::json::required(type, "type")
    )) {
        return widget;
    }

    util::switcher::string(type, {
        {"chart", [&widget, config, parent]() { widget = build<ChartWidget>(config, parent); }},
        {"button", [&widget, config, parent]() { widget = build<ButtonWidget>(config, parent); }},
        {"group",  [&widget, config, parent]() { widget = build<WidgetGroup>(config, parent); }}
    }, [&type]() {
        Log::err("WidgetFactory", "Unknown widget type '" + type + "'");
    });

    return widget;
}

void WidgetFactory::buildAll(const json& configs, WidgetGrid* layout, QWidget* parent)
{
    for (const json& el : configs) {
        widgets::Widget* widget = widgets::WidgetFactory::build<widgets::Widget>(el, parent);

        unsigned x, y, xspan, yspan;
        int width, height;

        if (widget && util::json::validate("Widget", el,
            util::json::required {x, "x"},
            util::json::required {y, "y"},
            util::json::optionnal {xspan, "colspan", 1u},
            util::json::optionnal {yspan, "rowspan", 1u},
            util::json::optionnal {width, "width", -1},
            util::json::optionnal {height, "height", -1}
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