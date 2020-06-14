#include <util/util.h>

template <>
bool has<std::string>(const json& j, const std::string& key)
{
    return j.count(key) && j[key].is_string();
}

template <>
bool has<double>(const json& j, const std::string& key)
{
    return j.count(key) && j[key].is_number();
}

template <>
bool has<int>(const json& j, const std::string& key)
{
    return j.count(key) && j[key].is_number_integer();
}

template <>
bool has<unsigned>(const json& j, const std::string& key)
{
    return j.count(key) && j[key].is_number_unsigned();
}

bool has_array(const json& j, const std::string& key, int size)
{
    return j.count(key) && j[key].is_array() && (size == -1 || j[key].size() == (std::size_t)size);
}