#include "data/time_series.hh"

#include <string>

#include <cxxabi.h>

#include <log/log.hh>
#include <util/time.hh>

namespace cute::data {

template <typename T>
TimeSeries<T>::TimeSeries(const std::string& source, uint64_t length)
    : Series()
{
    now_ = util::now<std::milli>;

    if (!subscribe<T>(source, [this](const auto& t, const T& v) {
        accept(
            std::chrono::duration_cast<std::chrono::milliseconds>(t),
            v
        );
    })) {
        int status;
        Log::err("TimeSeries") << "Could not subscribe to topic '" << source << "' with type " << abi::__cxa_demangle(typeid(T).name(), 0, 0, &status) << std::endl;
    }

    length_ = length;
}

template <typename T>
TimeSeries<T>::~TimeSeries() {}

template <typename T>
void TimeSeries<T>::accept(const std::chrono::milliseconds& when, const T& what)
{
    // if (sampling_policy_->accept(when, &what)) {
    const std::lock_guard<std::mutex> lock(mutex_);
    data_.push_back(std::make_pair(when.count(), what));

    if (data_.front().first < now_() - length_) {
        data_.erase(data_.begin());
    }
    // }
}

template class TimeSeries<double>;
template class TimeSeries<bool>;

} // namespaces