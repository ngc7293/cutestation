#ifndef TOPIC_CALLBACK_HH_
#define TOPIC_CALLBACK_HH_

#include <any>
#include <chrono>
#include <functional>
#include <utility>

#include "type.hh"

namespace topic {

class GenericCallback {
public:
    virtual ~GenericCallback() {}
    virtual void operator()(const topic::time&, const std::any&) const = 0;
};

template<typename T>
class Callback : public GenericCallback {
public:
    Callback(const std::function<void(const topic::time&, const T&)>& function)
    {
        function_ = function;
    }
    virtual ~Callback() {}

    void operator()(const topic::time& time, const std::any& value) const override
    {
        if (typeid(T) == value.type()) {
            function_(time, std::any_cast<const T&>(value));
        }
    }

private:
    std::function<void(const topic::time&, const T&)> function_;
};

}

#endif