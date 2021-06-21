#include "util/thread.hh"

#include <thread>

#if (defined _MSC_VER)
#include <windows.h>
#include <processthreadsapi.h>
#endif

namespace util::thread {

void rename_this_thread(const std::string& name)
{
#if (defined _MSC_VER)
    SetThreadDescription(GetCurrentThread(), std::wstring(name.begin(), name.end()).c_str());
#else
    pthread_setname_np(pthread_self(), name.c_str());
#endif
}

}