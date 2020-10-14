#include <util/json.hh>

namespace util::json {

template <>
bool has<std::string>(const nlohmann::json& j, const std::string& key)
{
    return j.count(key) && j[key].is_string();
}

template <>
bool has<double>(const nlohmann::json& j, const std::string& key)
{
    return j.count(key) && j[key].is_number();
}

template <>
bool has<int>(const nlohmann::json& j, const std::string& key)
{
    return j.count(key) && j[key].is_number_integer();
}

template <>
bool has<unsigned>(const nlohmann::json& j, const std::string& key)
{
    return j.count(key) && j[key].is_number_unsigned();
}

template <>
bool has<bool>(const nlohmann::json& j, const std::string& key)
{
    return j.count(key) && j[key].is_boolean();
}

bool has_array(const nlohmann::json& j, const std::string& key, int size)
{
    return j.count(key) && j[key].is_array() && (size == -1 || j[key].size() == (std::size_t)size);
}

}