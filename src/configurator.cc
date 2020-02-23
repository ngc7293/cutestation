#include "configurator.h"

#include <filesystem>
#include <fstream>

#include "data/series.h"
#include "data/series_factory.h"
#include "log.h"
#include "util.h"
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
    if (!has_array(config_, "widgets")) {
        Log::err("Configurator", "Missing or invalid mandatory top-level configuration 'widgets'");
        return false;
    }

    if (has_array(config_, "series")) {
        for (const auto& series_config: config_["series"]) {
            data::SeriesSP series = data::SeriesFactory::build(tree, series_config);
        }
    }

    for (const auto& widget_config: config_["widgets"]) {
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

    if (!(has_uint(config, "x") && has_uint(config, "y"))) {
        Log::err("Configurator", "Could not add widget '" + widget->name() + "': invalid x/y grid position");
        return false;
    }

    if (has_uint(config, "width")) {
        widget->setFixedWidth(config["width"].get<int>());
    }

    if (has_uint(config, "height")) {
        widget->setFixedHeight(config["height"].get<int>());
    }

    if (has_uint(config, "colspan")) {
        colspan = config["colspan"].get<int>();
    }

    if (has_uint(config, "rowspan")) {
        rowspan = config["rowspan"].get<int>();
    }

    layout.addWidget(widget, config["y"].get<int>(), config["x"].get<int>(), colspan, rowspan);
    return true;
}

} // namespace
