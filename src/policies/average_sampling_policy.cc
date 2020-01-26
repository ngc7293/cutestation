#include "policies/average_sampling_policy.h"

AverageSamplingPolicy::AverageSamplingPolicy(std::uint64_t period)
{
    period_ = period;
}

AverageSamplingPolicy::~AverageSamplingPolicy()
{
}

bool AverageSamplingPolicy::accept(std::uint64_t timestamp, float* value)
{
    if (timestamp - last_point_ > period_) {
        float temp = *value;
        *value = accumulated_ / count_;
        accumulated_ = temp;
        count_ = 1;
        last_point_ = timestamp;
        return true;
    } else {
        accumulated_ += *value;
        count_++;
        return false;
    }
}