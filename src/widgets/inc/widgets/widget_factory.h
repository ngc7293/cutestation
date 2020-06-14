#ifndef WIDGET_FACTORY_H_
#define WIDGET_FACTORY_H_

#include "nlohmann/json.hpp"

#include "widget.h"

using json = nlohmann::json;

namespace cute::widgets {

class WidgetFactory {
public:
    static Widget* build(const json& config);
};

} // namespaces

#endif