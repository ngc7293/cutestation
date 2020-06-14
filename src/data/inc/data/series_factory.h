#ifndef DATA_SERIES_FACTORY_H_
#define DATA_SERIES_FACTORY_H_

#include "nlohmann/json.hpp"

#include "series.h"

using json = nlohmann::json;

namespace cute::data {

class SeriesFactory {
public:
    static SeriesSP build(const json& config);
};

} // namespaces

#endif 