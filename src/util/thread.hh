#ifndef CUTE_UTIL_THREAD_HH_
#define CUTE_UTIL_THREAD_HH_

#include <string>

namespace util::thread {

void rename_this_thread(const std::string& name);

}

#endif