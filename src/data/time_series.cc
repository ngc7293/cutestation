#include "data/time_series.h"

#include <string>

#include "proto/packet.h"
#include "util.h"

#include "log.h"

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

    if (!has_uint(config, "length")) {
        Log::err("TimeSeries", "missing or invalid mandatory configuration 'length'");
        return false;
    }
    length_ = config["length"].get<std::uint64_t>();

    return true;
}

template <typename T>
void TimeSeries<T>::accept(const proto::Measurement& measurement)
{
    T value = extractValue(measurement);

    if (sampling_policy_->accept(measurement.timestamp(), &value)) {
        const std::lock_guard<std::mutex> lock(mutex_);
        data_.push_back(std::make_pair(measurement.timestamp(), value));

        if (data_.front().first < now() - length_) {
            data_.erase(data_.begin());
        }
    }
}

template <>
double TimeSeries<double>::extractValue(const proto::Measurement& measurement) const
{
    return measurement.float_();
}

template class TimeSeries<double>;

} // namespaces