#ifndef SAMPLING_POLICY_H_
#define SAMPLING_POLICY_H_

#include <memory>

#include <cstdint>

class SamplingPolicy;
typedef std::shared_ptr<SamplingPolicy> SamplingPolicySP;

/** A sampling policy defines a signal processing strategy, must generally a form of decimation */
class SamplingPolicy {

public:
    SamplingPolicy();
    virtual ~SamplingPolicy();

    virtual bool accept(std::uint64_t timestamp, double* value) = 0;
};

#endif