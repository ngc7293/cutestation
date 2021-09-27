#ifndef UTIL_TYPE_HH_
#define UTIL_TYPE_HH_

#include <string>

#include <cassert>

#ifdef __GNUC__
#include <cxxabi.h>
#endif

namespace util::type {

inline const char* name(const std::type_info& type)
{
#ifdef __GNUC__
    int status = 0;
    const char* ret = abi::__cxa_demangle(type.name(), 0, 0, &status);
    assert(status == 0);
    return ret;
#elif _MSC_VER
    return type.name();
#endif
}

template<typename Type>
inline const char* name()
{
    return name(typeid(Type));
}

template<>
inline const char* name<std::string>()
{
    return "string";
}

}

#endif