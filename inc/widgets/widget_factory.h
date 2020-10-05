#ifndef WIDGET_FACTORY_H_
#define WIDGET_FACTORY_H_

#include "nlohmann/json.hpp"

#include "widget.h"

#include "data/series.h"
#include "data/command.h"

using json = nlohmann::json;

namespace cute::widgets {

class WidgetFactory {
public:
    static Widget* build(data::SeriesSP& series, data::CommandSP& command, const json& config);
};

} // namespaces

#endif