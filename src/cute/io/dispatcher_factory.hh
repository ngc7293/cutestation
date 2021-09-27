#ifndef CUTE_IO_DISPATCHERFACTORY_HH_
#define CUTE_IO_DISPATCHERFACTORY_HH_

#include <memory>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace cute::io {

class DispatcherFactory {
public:
    template<class T>
    static std::shared_ptr<T> build(const json& config); 

    template<class T>
    static std::vector<std::shared_ptr<T>> buildAll(const json& config); 
};

}

#endif