#ifndef WIDGET_FACTORY_HH_
#define WIDGET_FACTORY_HH_

#include "nlohmann/json.hpp"

#include "widget.hh"
#include "widget_grid.hh"

using json = nlohmann::json;

namespace cute::widgets {

class WidgetFactory {
public:
    // Note that unlike other build() functions in this project, WidgetFactory
    // uses a non-smart pointer to return the value, this is to have easier
    // integration with Qt.
    template<class T>
    static T* build(const json& config, QWidget* parent = nullptr);

    static void buildAll(const json& configs, WidgetGrid* layout, QWidget* parent = nullptr);
};

} // namespaces

#endif