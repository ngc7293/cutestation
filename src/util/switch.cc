#include "util/switch.hh"

namespace util::switcher {

bool string(const std::string& string, std::initializer_list<_switch_initializer> list, std::function<void()> def)
{
    for (const _switch_initializer& si: list) {
        if (string == si.s) {
            si.f();
            return true;
        }
    }

    def();
    return false;
}

}