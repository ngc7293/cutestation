#ifndef CUTE_WIDGETS_RANGEMAPPING_H_
#define CUTE_WIDGETS_RANGEMAPPING_H_

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

namespace cute::widgets {

template<typename Type>
struct RangeMapping {
    Type low, high;
    std::string displayFormat;
    std::string color, backgroundColor;

    static std::optional<RangeMapping<Type>> build(const std::string& key, const nlohmann::json& value);
    static std::vector<RangeMapping<Type>> buildAll(const nlohmann::json& json);
};

}

#endif