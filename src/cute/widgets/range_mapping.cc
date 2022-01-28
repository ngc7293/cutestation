#include <log/log.hh>
#include <util/json.hh>

#include "range_mapping.hh"

namespace cute::widgets {

template<typename Type>
std::optional<RangeMapping<Type>> RangeMapping<Type>::build(const std::string& key, const nlohmann::json& value)
{
    RangeMapping<Type> mapping;

    try {
        auto pos = key.find("~");

        if (pos == std::string::npos) {
            mapping.low = std::stol(key);
            mapping.high = mapping.low;
        } else {
            if (pos == 0) {
                mapping.low = std::numeric_limits<Type>::min();
            } else {
                mapping.low = std::stol(key.substr(0, pos));
            }

            if (pos == key.length() - 1) {
                mapping.high = std::numeric_limits<Type>::max();
            } else {
                mapping.high = std::stol(key.substr(pos + 1, key.length()));
            }
        }
    } catch (...) {
        logging::err("RangeMapping") << "Could not parse range key '" << key << "'" << logging::endl;
        return {};
    }

    if (value.is_object()) {
        if (!(util::json::validate("RangeMapping", value,
            util::json::required(mapping.displayFormat, "displayFormat"),
            util::json::optional(mapping.color, "color", ""),
            util::json::optional(mapping.backgroundColor, "background", "")
        ))) {
            return {};
        }
    } else if (value.is_string()) {
        mapping.displayFormat = value.get<std::string>();
    } else {
        logging::err("RangeMapping") << "Invalid JSON type for mapping element" << logging::endl;
        return {};
    }

    return {std::move(mapping)};
}

template<typename Type>
std::vector<RangeMapping<Type>> RangeMapping<Type>::buildAll(const nlohmann::json& json)
{
    std::vector<RangeMapping<Type>> mappings;

    for (const auto& [key, value]: json.items()) {
        auto maybe = RangeMapping<Type>::build(key, value);

        if (maybe) {
            mappings.emplace_back(maybe.value());
        }
    }

    std::sort(mappings.begin(), mappings.end(), [](const auto& lhs, const auto& rhs) { return lhs.low < rhs.low; });
    for (std::size_t i = 0; i < mappings.size() - 1; i++) {
        if (mappings[i].high > mappings[i + 1].low) {
            logging::err("RangeMapping") << "Overlapping mapping configuration" << logging::endl;
            return {};
        }
    }

    for (const auto& m: mappings) {
        logging::debug("RangeMapping") 
            << logging::tag{"low", m.low}
            << logging::tag{"high", m.high}
            << logging::tag{"display", m.displayFormat}
            << logging::tag{"color", m.color}
            << logging::tag{"background", m.backgroundColor}
            << logging::endl;
    }

    return mappings;
}

template struct RangeMapping<int>;
template struct RangeMapping<double>;

}