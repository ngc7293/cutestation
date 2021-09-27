#ifndef CUTE_DATA_SERIESFACTORY_HH_
#define CUTE_DATA_SERIESFACTORY_HH_

#include "nlohmann/json.hpp"

#include "series.hh"

using json = nlohmann::json;

namespace cute::data {

class SeriesFactory {
public:
    template<class T>
    static std::shared_ptr<T> build(const json& config);
};

} // namespaces

#endif 