#ifndef TIME_SERIES_H_
#define TIME_SERIES_H_

#include "series.h"

#include <deque>
#include <memory>
#include <mutex>
#include <utility>

#include <QVector>
#include <QPointF>

namespace cute::data {

template<typename T>
class TimeSeries : public Series {
private:
    std::deque<std::pair<std::uint64_t, T>> data_;
    mutable std::mutex mutex_;

    std::uint64_t length_;

public:
    TimeSeries();
    ~TimeSeries() override;

    virtual bool init(SamplingPolicySP sampling_policy, const json& config) override;

    void accept(const proto::Measurement& measurement) override;

    size_t size() const {
        const std::lock_guard<std::mutex> lock(mutex_);
        return data_.size();
    }

    T first() const {
        const std::lock_guard<std::mutex> lock(mutex_);
        return data_.front().second;
    }

    T last() const { 
        const std::lock_guard<std::mutex> lock(mutex_);
        return data_.back().second;
    }

    /** TimeSeries::data(container)
     * Export the TimeSeries's data to a different container format/class to
     * allow use with different libraries (e.g.: Qt) with minimal copying
     * 
     * requires U<V> to implement `reserve()` and `push_back`
     * requires V to be construtable with (time, value)
     */
    template<template<typename> class U, typename V>
    void data(U<V>& container) const {
        // Have to put implementation here because of  template class
        // compilation behavior
        const std::lock_guard<std::mutex> lock(mutex_);
        container.reserve(data_.size());

        for (const auto& point : data_) {
            container.push_back(V(point.first, point.second));
        }
    }

private:
    /** TimeSeries::extractValue()
     * Extracts the template-appropriate value from the protobuf Packet
     */
    T extractValue(const proto::Measurement& measurement) const;
};

template<typename T>
using TimeSeriesSP = std::shared_ptr<TimeSeries<T>>;

} // namespaces

#endif