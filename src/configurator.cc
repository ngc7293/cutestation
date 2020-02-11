#include "configurator.h"

#include <filesystem>
#include <fstream>

#include "data/series.h"
#include "data/series_factory.h"
#include "log.h"
#include "widgets/widget_factory.h"

namespace cute {

Configurator::Configurator() {}

Configurator::~Configurator() {}

bool Configurator::load(std::string file)
{
    if (!std::filesystem::exists(std::filesystem::path(file))) {
        Log::err("Configurator", "No such file '" + file + "'");
    }

    std::ifstream ifs(file);
    if (ifs.fail()) {
        Log::err("Configurator", "Error opening file '" + file + "'");
    }

    config_ = json::parse(ifs);
    return true;
}

bool Configurator::configure(QGridLayout& layout, data::Tree& tree)
{
    if (config_.count("widgets") != 1) {
        Log::err("Configurator", "'widgets' is required");
        return false;
    }

    if (!config_["widgets"].is_array()) {
        Log::err("Configurator", "'widgets' must be an array");
        return false;
    }

    for (const auto& widget_config : config_["widgets"]) {
        data::SeriesSP series = data::SeriesFactory::build(tree, widget_config);

        if (!series) {
            continue;
        }

        widgets::Widget* widget = widgets::WidgetFactory::build(series, widget_config);
        if (!widget) {
            // TODO: Remove the series/data object if no one else refers to it?
            continue;
        }
        widget->setParent(layout.parentWidget());

        if (!addToGrid(layout, widget, widget_config)) {
            delete widget;
        }
    }

    return true;
}

bool Configurator::addToGrid(QGridLayout& layout, widgets::Widget* widget, const json& config)
{
    int rowspan = 1, colspan = 1;

    if (!(config.count("x") && config.count("y") && config["x"].is_number_unsigned() && config["y"].is_number_unsigned())) {
        Log::err("Configurator", "Could not add widget '" + widget->name() + "': invalid x/y grid position");
        return false;
    }

    if (config.count("width") && config["width"].is_number_unsigned()) {
        widget->setFixedWidth(config["width"].get<int>());
    }

    if (config.count("height") && config["height"].is_number_unsigned()) {
        widget->setFixedHeight(config["height"].get<int>());
    }

    if (config.count("colspan") && config["colspan"].is_number_unsigned()) {
        colspan = config["colspan"].get<int>();
    }

    if (config.count("rowspan") && config["rowspan"].is_number_unsigned()) {
        rowspan = config["rowspan"].get<int>();
    }

    layout.addWidget(widget, config["y"].get<int>(), config["x"].get<int>(), colspan, rowspan);
    return true;
}

} // namespace
