#ifndef CUTE_DATA_TIME_SERIES_HH_
#define CUTE_DATA_TIME_SERIES_HH_

#include "series.hh"

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

    std::function<uint64_t(void)> now_;
    std::uint64_t length_;

public:
    TimeSeries(const std::string& source, uint64_t length);
    ~TimeSeries() override;

    size_t size() const {
        const std::lock_guard<std::mutex> lock(mutex_);
        return data_.size();
    }

    uint64_t length() const {
        const std::lock_guard<std::mutex> lock(mutex_);
        return length_;
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
     * requires V to be construtable with (uint64_t time, T value)
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

    /** TimeSeries::set_now
     * Lets you override the now() function TimeSeries uses to check data's age.
     */
    void set_now(std::function<uint64_t(void)> now) {
        const std::lock_guard<std::mutex> lock(mutex_);
        now_ = now;
    }

private:
    void accept(const std::chrono::milliseconds& when, const T& what);
};

} // namespaces

#endif