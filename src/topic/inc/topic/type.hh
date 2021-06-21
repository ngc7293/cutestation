#ifndef TOPIC_TYPE_HH_
#define TOPIC_TYPE_HH_

#include <chrono>
#include <variant>

namespace topic {
    using time = std::chrono::milliseconds;
    using clock = std::chrono::system_clock;

/* TODO: Investigate the performance impact of using std::any vs std::variant,
         and switch to it if the performance improvement is significant. In such
         a scenario, we will want to restrict types to the following below. I'd
         want to call them simply topic::int, topic::bool, etc. but C++ (or GCC)
         has something to say about redefining built-in types.

    using std::variant<boolean, integer, floating, string> = value; */
}

#endif