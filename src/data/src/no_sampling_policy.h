#ifndef NO_SAMPLING_POLICY_H_
#define NO_SAMPLING_POLICY_H_

#include "data/sampling_policy.h"

/** A void sampling policies that accepts all data as-is without decimation */
class NoSamplingPolicy : public SamplingPolicy {

public:
    NoSamplingPolicy();
    ~NoSamplingPolicy() override;

    bool accept(std::uint64_t timestamp, double* value) override;
};

#endif