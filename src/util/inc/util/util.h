#ifndef UTIL_H_
#define UTIL_H_

#include <chrono>
#include <ratio>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/** now<Unit>
 * Returns the current time in `Unit` seconds since epoch. `Unit` should be one
 * of the std::ratio classes.
 * 
 * @return time in `Unit`-seconds since epoch
 */
template <class Unit>
std::uint64_t now()
{
    return std::chrono::duration_cast<std::chrono::duration<std::uint64_t, Unit>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

/** has<T>
 * Check if JSON object contains key of type T
 * 
 * @param key key to look for
 * 
 * @return true if such a key of type T is found, false otherwise
 */
template <typename T>
bool has(const json& j, const std::string& key);

/** has_array
 * Checks if JSON contains an array for a given key
 *
 * @param j    json to check
 * @param key  key to look for
 * @param size expected size of array, -1 for any (default)
 *
 * @return true/false
 */
bool has_array(const json& j, const std::string& key, int size = -1);

#endif