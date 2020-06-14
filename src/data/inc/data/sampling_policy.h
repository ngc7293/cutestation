#ifndef SAMPLING_POLICY_H_
#define SAMPLING_POLICY_H_

#include <memory>

class SamplingPolicy {

public:
    SamplingPolicy();
    virtual ~SamplingPolicy();

    virtual bool accept(std::uint64_t timestamp, double* value) = 0;
};

typedef std::shared_ptr<SamplingPolicy> SamplingPolicySP;

#endif