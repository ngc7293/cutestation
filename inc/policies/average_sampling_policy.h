#ifndef AVERAGE_SAMPLING_POLICY_H_
#define AVERAGE_SAMPLING_POLICY_H_

#include "sampling_policy.h"

#include <cstdint>

class AverageSamplingPolicy : public SamplingPolicy {

private:
    std::uint64_t last_point_, period_;
    float accumulated_;
    int count_;

public:
    AverageSamplingPolicy(std::uint64_t period);
    ~AverageSamplingPolicy();

    bool accept(std::uint64_t timestamp, float* value) override;
};

#endif