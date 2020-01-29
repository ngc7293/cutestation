#ifndef WIDGET_FACTORY_H_
#define WIDGET_FACTORY_H_

#include "nlohmann/json.hpp"

#include "widget.h"

#include "data/series.h"

using json = nlohmann::json;

namespace cute { namespace widgets {

class WidgetFactory {
public:
    static Widget* build(data::SeriesSP& series, const json& config);
};

}} // namespaces

#endif