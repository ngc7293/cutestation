#ifndef UTIL_H_
#define UTIL_H_

#include <chrono>
#include <cstdint>

/** now
 * Get system clock in milliseconds
 * 
 * @return milliseconds since epoch
 */
std::uint64_t now();

#endif