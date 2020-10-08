#include "configurator.h"

#include <filesystem>
#include <fstream>

#include <log/log.hh>
#include <util/util.h>
#include <widgets/widget_factory.h>

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

bool Configurator::configure(QGridLayout& layout)
{
    if (!has_array(config_, "widgets")) {
        Log::err("Configurator", "Missing or invalid mandatory top-level configuration 'widgets'");
        return false;
    }

    for (const auto& widget_config: config_["widgets"]) {
        widgets::Widget* widget = widgets::WidgetFactory::build(widget_config);
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

    if (!(has<unsigned>(config, "x") && has<unsigned>(config, "y"))) {
        Log::err("Configurator", "Could not add widget '" + widget->name() + "': invalid x/y grid position");
        return false;
    }

    if (has<unsigned>(config, "width")) {
        widget->setFixedWidth(config["width"].get<int>());
    }

    if (has<unsigned>(config, "height")) {
        widget->setFixedHeight(config["height"].get<int>());
    }

    if (has<unsigned>(config, "colspan")) {
        colspan = config["colspan"].get<int>();
    }

    if (has<unsigned>(config, "rowspan")) {
        rowspan = config["rowspan"].get<int>();
    }

    layout.addWidget(widget, config["y"].get<int>(), config["x"].get<int>(), colspan, rowspan);
    return true;
}

} // namespace
