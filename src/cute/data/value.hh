#ifndef CUTE_DATA_VALUE_HH_
#define CUTE_DATA_VALUE_HH_

#include <mutex>

#include <util/time.hh>

namespace cute::data {

template<typename Type>
class Value {
public:
    Value() = default;
    virtual ~Value() = default;

    virtual Type value() const = 0;
    virtual std::chrono::milliseconds timestamp() const = 0;
};

template<typename Type>
class StaticValue: public Value<Type> {
public:
    StaticValue(Type value)
        : data_(util::time::now<std::chrono::milliseconds>(), value)
    {
    }
    ~StaticValue() = default;

    Type value() const override { return data_.second; };
    std::chrono::milliseconds timestamp() const override { return data_.first; };

private:
    std::pair<std::chrono::milliseconds, Type> data_;

};

using NumberValue = Value<double>;
using StateValue = Value<int>;
using StringValue = Value<std::string>;

}

#endif