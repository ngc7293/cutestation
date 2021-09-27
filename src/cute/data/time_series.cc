#include <deque>
#include <memory>
#include <mutex>

#include "time_series.hh"

namespace cute::data {

TimeSeriesIterator::reference TimeSeriesIterator::operator*() const
{
    return *it_; 
}

TimeSeriesIterator::pointer TimeSeriesIterator::operator->() const
{
    return &(*it_);
}

TimeSeriesIterator& TimeSeriesIterator::operator++()
{
    ++it_;
    return *this;
}

TimeSeriesIterator& TimeSeriesIterator::operator--()
{
    --it_;
    return *this;
}

TimeSeriesIterator::TimeSeriesIterator(const std::deque<value_type>& container, std::chrono::milliseconds now)
    : it_(container.begin())
    , now_(now)
{
    while (it_ != container.end() && it_->first < now_) {
        ++it_;
    }
}

TimeSeriesIterator::TimeSeriesIterator(const std::deque<value_type>& container)
    : it_(container.end())
    , now_(0)
{
}

bool operator==(const TimeSeriesIterator& lhs, const TimeSeriesIterator& rhs)
{
    return lhs.it_ == rhs.it_;
}

bool operator!=(const TimeSeriesIterator& lhs, const TimeSeriesIterator& rhs)
{
    return !(lhs == rhs);
}

TimeSeries::TimeSeries(std::chrono::milliseconds length)
{
    now_ = util::time::now<std::chrono::milliseconds>;
    length_ = length;
}

TimeSeries::TimeSeries(const std::string& source, std::chrono::milliseconds length)
{
    now_ = util::time::now<std::chrono::milliseconds>;

    if (!subscriber_.subscribe<double>(source, [this](const topic::time& t, const double& v) {
        accept(std::chrono::duration_cast<std::chrono::milliseconds>(t), v);
    })) {
        logging::err("TimeSeries") << "Could not subscribe to topic '" << source << "' with type double" << logging::endl;
    }

    length_ = length;
}

TimeSeries::~TimeSeries() = default;

void TimeSeries::accept(const std::chrono::milliseconds& when, const double& what)
{
    const std::lock_guard<std::mutex> lock(mutex_);
    if (!(data_.size() != 0 && when < data_.back().first)) {
        data_.emplace_back(when, what);
    }

    if (data_.front().first < now_() - length_) {
        data_.erase(data_.begin());
    }
}


size_t TimeSeries::size() const
{
    const std::lock_guard<std::mutex> lock(mutex_);
    return data_.size();
}

std::chrono::milliseconds TimeSeries::length() const
{
    const std::lock_guard<std::mutex> lock(mutex_);
    return length_;
}

TimeSeriesIterator TimeSeries::begin() const
{
    return TimeSeriesIterator(data_, now_() - length_);
}

TimeSeriesIterator TimeSeries::end() const
{
    return TimeSeriesIterator(data_);
}

std::pair<std::chrono::milliseconds, double> TimeSeries::front() const
{
    const std::lock_guard<std::mutex> lock(mutex_);
    return data_.front();
}

std::pair<std::chrono::milliseconds, double> TimeSeries::back() const
{
    const std::lock_guard<std::mutex> lock(mutex_);
    return data_.back();
}

void TimeSeries::set_now(std::function<std::chrono::milliseconds(void)> now)
{
    const std::lock_guard<std::mutex> lock(mutex_);
    now_ = now;
}

} // namespaces