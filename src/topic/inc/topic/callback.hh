#ifndef TOPIC_CALLBACK_HH_
#define TOPIC_CALLBACK_HH_

#include <any>
#include <chrono>
#include <functional>
#include <utility>

namespace topic {

class GenericCallback {
public:
    virtual ~GenericCallback() {}
    virtual void operator()(const std::chrono::nanoseconds&, const std::any&) const = 0;
};

template<typename T>
class Callback : public GenericCallback {
public:
    Callback(const std::function<void(const std::chrono::nanoseconds&, const T&)>& function)
    {
        function_ = function;
    }
    virtual ~Callback() {}

    void operator()(const std::chrono::nanoseconds& time, const std::any& value) const override
    {
        if (typeid(T) == value.type()) {
            function_(time, std::any_cast<const T&>(value));
        }
    }

private:
    std::function<void(const std::chrono::nanoseconds&, const T&)> function_;
};

}

#endif