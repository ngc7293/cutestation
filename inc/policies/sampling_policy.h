#ifndef SAMPLING_POLICY_H_
#define SAMPLING_POLICY_H_

#include <cstdint>

/** A sampling policy defines a signal processing strategy, must generally a form of decimation */
class SamplingPolicy {

public:
    SamplingPolicy();
    ~SamplingPolicy();

    virtual bool accept(std::uint64_t timestamp, float* value) = 0;
};

#endif