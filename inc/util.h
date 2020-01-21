#ifndef UTIL_H_
#define UTIL_H_

#include <chrono>
#include <cstdint>

/** now
 * Get system clock in milliseconds
 * 
 * @return milliseconds since epoch
 */
std::uint64_t now() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }

#endif