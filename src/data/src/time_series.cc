#include "data/time_series.hh"

#include <string>

#ifdef __GNUC__
#include <cxxabi.h>
#endif

#include <log/log.hh>
#include <util/time.hh>

namespace cute::data {

template <typename T>
TimeSeries<T>::TimeSeries(const std::string& source, uint64_t length)
    : Series()
{
    now_ = util::time::now<std::milli>;

    if (!subscriber_.subscribe<T>(source, [this](const topic::time& t, const T& v) {
        accept(std::chrono::duration_cast<std::chrono::milliseconds>(t), v);
    })) {
        int status;
        logging::err("TimeSeries") << "Could not subscribe to topic '" << source << "' with type " << 
#ifdef __GNUC__
            abi::__cxa_demangle(typeid(T).name(), 0, 0, &status)
#elif _MSC_VER
            typeid(T).name()
#endif
        << logging::endl;
    }

    length_ = length;
}

template <typename T>
TimeSeries<T>::~TimeSeries() {}

template <typename T>
void TimeSeries<T>::accept(const std::chrono::milliseconds& when, const T& what)
{
    const std::lock_guard<std::mutex> lock(mutex_);
    data_.push_back(std::make_pair(when.count(), what));

    if (data_.front().first < now_() - length_) {
        data_.erase(data_.begin());
    }
}

template class TimeSeries<double>;

} // namespaces