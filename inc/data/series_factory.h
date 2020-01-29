#ifndef SERIES_FACTORY_H_
#define SERIES_FACTORY_H_

#include "nlohmann/json.hpp"

#include "series.h"
#include "tree.h"

using json = nlohmann::json;

namespace cute { namespace data {

class SeriesFactory {
public:
    static SeriesSP build(Tree& tree, const json& config);
};

}} // namespaces

#endif 