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

        layout.addWidget(widget, widget_config["x"].get<int>(), widget_config["y"].get<int>());
    }

    return true;
}

} // namespace
