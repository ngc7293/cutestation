#ifndef CUTE_DATA_SINGLEVALUE_HH_
#define CUTE_DATA_SINGLEVALUE_HH_

#include <mutex>

#ifdef __GNUC__
#include <cxxabi.h>
#endif

#include <log/log.hh>
#include <topic/subscriber.hh>

namespace cute::data {

template<typename Type>
class SingleValue {
public:
    SingleValue(const std::string& source) {
        if (!subscriber_.subscribe<Type>(source, [this](const auto& t, const Type& v) {
            std::lock_guard<std::mutex> _(mutex_);
            accept(t, v);
        })) {
            int status;
            logging::err("TimeSeries") << "Could not subscribe to topic '" << source << "' with type " << 
#ifdef __GNUC__
            abi::__cxa_demangle(typeid(Type).name(), 0, 0, &status)
#elif _MSC_VER
            typeid(T).name()
#endif
            << logging::endl;
        }
    }

    virtual ~SingleValue() = default;

    Type value() const {
        std::lock_guard<std::mutex> _(mutex_);
        return data_.second;
    }

    virtual void accept(const std::chrono::milliseconds& when, const Type& what) = 0;

private:
    topic::Subscriber subscriber_;
    mutable std::mutex mutex_;

protected:
    std::pair<std::uint64_t, Type> data_;
};

}

#endif