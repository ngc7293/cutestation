#ifndef CUTE_DATA_AVERAGEVALUE_HH_
#define CUTE_DATA_AVERAGEVALUE_HH_

#include "dynamic_value.hh"
#include "time_series.hh"

namespace cute::data {

class RollingAverageValue : public DynamicValue {
public:
    RollingAverageValue(const std::string& source, std::chrono::milliseconds window);

    double value() const override;
    std::chrono::milliseconds timestamp() const override;

    void accept(const std::chrono::milliseconds& when, const double& what) override;

    TimeSeries& series();

private:
    std::unique_ptr<TimeSeries> series_;
};

}

#endif