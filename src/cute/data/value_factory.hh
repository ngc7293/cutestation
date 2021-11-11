#ifndef CUTE_DATA_VALUEFACTORY_HH_
#define CUTE_DATA_VALUEFACTORY_HH_

#include "nlohmann/json.hpp"

#include "value.hh"

using json = nlohmann::json;

namespace cute::data {

class ValueFactory {
public:
    static Value* build(const json& config);
};

} // namespaces

#endif 