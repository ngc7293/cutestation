#ifndef CUTE_DATA_MINMAXVALUES_HH_
#define CUTE_DATA_MINMAXVALUES_HH_

#include "data/single_value.hh"

namespace cute::data {

template<typename Type>
class MinValue : public SingleValue<Type> {
public:
    MinValue(const std::string& source) : SingleValue<Type>(source) { }
    ~MinValue() = default;

    void accept(const std::chrono::milliseconds& when, const Type& what) override {
        if (what < SingleValue<Type>::data_.second) {
            SingleValue<Type>::data_ = {when.count(), what};
        }
    }
};

template<typename Type>
class MaxValue : public SingleValue<Type> {
public:
    MaxValue(const std::string& source) : SingleValue<Type>(source) { }
    ~MaxValue() = default;

    void accept(const std::chrono::milliseconds& when, const Type& what) override {
        if (what > SingleValue<Type>::data_.second) {
            SingleValue<Type>::data_ = {when.count(), what};
        }
    }
};

}

#endif