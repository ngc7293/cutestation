#include "average_value.hh"

namespace cute::data {

RollingAverageValue::RollingAverageValue(const std::string& source, std::chrono::milliseconds window)
    : DynamicValue<double>(source)
{
    series_.reset(new TimeSeries(window));
}

double RollingAverageValue::value() const
{
    uint64_t count = 0;
    double sum = 0;

    for (const auto& point: *series_) {
        sum += point.second;
        count++;
    }

    return count ? sum / count : 0.0;
}

std::chrono::milliseconds RollingAverageValue::timestamp() const
{
    return std::chrono::milliseconds(series_->back().first);
}

void RollingAverageValue::accept(const std::chrono::milliseconds& when, const double& what)
{
    series_->accept(when, what);
}

TimeSeries& RollingAverageValue::series()
{
    return *series_;
}

} // namespaces