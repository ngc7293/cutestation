#include <log/log.hh>
#include <util/json.hh>
#include <util/switch.hh>

#include "value_factory.hh"
#include "value.hh"
#include "dynamic_value.hh"
#include "average_value.hh"

namespace cute::data {

Value* ValueFactory::build(const json& config)
{
    if (config.is_number()) {
        return new StaticValue(config.get<double>());
    } else if (config.is_string()) {
        return new LastValue(config.get<std::string>());
    } else if (!config.is_object()) {
        logging::err("Value") << "Invalid JSON type" << logging::endl;
        return nullptr;
    }

    std::string type, source;

    if (!util::json::validate("Value", config,
        util::json::required(type, "type"),
        util::json::required(source, "source")
    )) {
        return nullptr;
    };

    Value* value;
    util::switcher::string(type, {
        {"min", [&] { value = new data::MinValue(source); }},
        {"max", [&] { value = new data::MaxValue(source); }},
        {"last", [&] { value = new data::LastValue(source); }},
    }, [&] {
        logging::err("Value") << "Invalid type '" << type << "'" << logging::endl;
    });

    return value;
}

} // namespaces