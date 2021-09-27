#ifndef CUTE_DATA_TIMESERIES_HH_
#define CUTE_DATA_TIMESERIES_HH_

#include "series.hh"

#include <deque>
#include <memory>
#include <mutex>

#include <log/log.hh>
#include <topic/subscriber.hh>
#include <util/time.hh>
#include <util/type.hh>

namespace cute::data {

class TimeSeriesIterator {
public:
    using value_type = std::pair<std::chrono::milliseconds, double>;
    using pointer = const value_type*;
    using reference = const value_type&;
    using iterator_category = std::output_iterator_tag;

public:
    reference operator*() const;
    pointer operator->() const;

    TimeSeriesIterator& operator++();
    TimeSeriesIterator& operator--();

    TimeSeriesIterator(const std::deque<value_type>& container, std::chrono::milliseconds now);
    TimeSeriesIterator(const std::deque<value_type>& container);

    friend bool operator==(const TimeSeriesIterator& lhs, const TimeSeriesIterator& rhs);
    friend bool operator!=(const TimeSeriesIterator& lhs, const TimeSeriesIterator& rhs);

private:
    std::deque<value_type>::const_iterator it_;
    std::chrono::milliseconds now_;
};

class TimeSeries : public Series {
public:
    TimeSeries(std::chrono::milliseconds length);
    TimeSeries(const std::string& source, std::chrono::milliseconds length);
    ~TimeSeries() override;

    void accept(const std::chrono::milliseconds& when, const double& what);

    size_t size() const;
    std::chrono::milliseconds length() const;

    TimeSeriesIterator begin() const;
    TimeSeriesIterator end() const;

    std::pair<std::chrono::milliseconds, double> front() const;
    std::pair<std::chrono::milliseconds, double> back() const;

    /** TimeSeries::data(container)
     * Export the TimeSeries's data to a different container format/class to
     * allow use with different libraries (e.g.: Qt) with minimal copying
     *
     * requires U<V> to implement `reserve()` and `push_back`
     * requires V to be construtable with (uint64_t time, T value)
     */
    template<template<typename> class U, typename V>
    void data(U<V>& container) const
    {
        // Have to put implementation here because of  template class
        // compilation behavior
        const std::lock_guard<std::mutex> lock(mutex_);
        container.reserve(static_cast<int>(data_.size()));

        for (const auto& point: *this) {
            container.push_back(V(point.first.count(), point.second));
        }
    }

    /** TimeSeries::set_now
     * Lets you override the now() function TimeSeries uses to check data's age.
     */
    void set_now(std::function<std::chrono::milliseconds(void)> now);

private:
    std::deque<std::pair<std::chrono::milliseconds, double>> data_;
    mutable std::mutex mutex_;
    topic::Subscriber subscriber_;

    std::function<std::chrono::milliseconds(void)> now_;
    std::chrono::milliseconds length_;
};

} // namespaces

#endif