#include "data/time_series.h"

#include <string>

#include <cxxabi.h>

#include "packet.pb.h"
#include <util/util.h>

#include <log/log.h>

namespace cute::data {

template <typename T>
TimeSeries<T>::TimeSeries() {}

template <typename T>
TimeSeries<T>::~TimeSeries() {}

template <typename T>
bool TimeSeries<T>::init(SamplingPolicySP sampling_policy, const json& config)
{
    if (!Series::init(sampling_policy, config)) {
        return false;
    }

    if (!has<std::string>(config, "source")) {
        Log::err("TimeSeries", "missing or invalid mandatory configuration 'source'");
        return false;
    }

    if (!subscribe<T>(config["source"].get<std::string>(), [this](const auto& t, const T& v) {
        accept(
            std::chrono::duration_cast<std::chrono::milliseconds>(t),
            v
        );
    })) {
        int status;
        Log::err("TimeSeries") << "Could not subscribe to topic '" << config["source"].get<std::string>() << "' with type " << abi::__cxa_demangle(typeid(T).name(), 0, 0, &status) << std::endl;
    } else {
        int status;
        Log::info("TimeSeries") << "Subscribed to topic '" << config["source"].get<std::string>() << "' with type " << abi::__cxa_demangle(typeid(T).name(), 0, 0, &status) << std::endl;
    }

    if (!has<unsigned>(config, "length")) {
        Log::err("TimeSeries", "missing or invalid mandatory configuration 'length'");
        return false;
    }
    length_ = config["length"].get<std::uint64_t>();

    return true;
}

template <typename T>
void TimeSeries<T>::accept(const std::chrono::milliseconds& when, const T& what)
{
    // if (sampling_policy_->accept(when, &what)) {
    const std::lock_guard<std::mutex> lock(mutex_);
    data_.push_back(std::make_pair(when.count(), what));

    if (data_.front().first < (now<std::milli>()) - length_) {
        data_.erase(data_.begin());
    }
    // }
}

template class TimeSeries<double>;
template class TimeSeries<bool>;

} // namespaces