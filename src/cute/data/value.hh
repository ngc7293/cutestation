#ifndef CUTE_DATA_VALUE_HH_
#define CUTE_DATA_VALUE_HH_

#include <mutex>

#include <util/time.hh>

namespace cute::data {

class Value {
public:
    Value() = default;
    virtual ~Value() = default;

    virtual double value() const = 0;
    virtual std::chrono::milliseconds timestamp() const = 0;
};

class StaticValue: public Value {
public:
    StaticValue(double value)
        : data_(util::time::now<std::chrono::milliseconds>(), value)
    {
    }
    ~StaticValue() = default;

    double value() const override { return data_.second; };
    std::chrono::milliseconds timestamp() const override { return data_.first; };

private:
    std::pair<std::chrono::milliseconds, double> data_;

};

}

#endif