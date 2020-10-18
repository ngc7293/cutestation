#ifndef WIDGET_FACTORY_H_
#define WIDGET_FACTORY_H_

#include "nlohmann/json.hpp"

#include "widget.hh"

using json = nlohmann::json;

namespace cute::widgets {

class WidgetFactory {
public:
    // Note that unlike other build() functions in this project, WidgetFactory
    // uses a non-smart pointer to return the value, this is to have easier
    // integration with Qt.
    template<class T>
    static T* build(const json& config, QWidget* parent = nullptr);
};

} // namespaces

#endif