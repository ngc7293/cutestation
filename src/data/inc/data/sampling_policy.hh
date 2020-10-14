#ifndef CUTE_DATA_SAMPLING_POLICY_HH_
#define CUTE_DATA_SAMPLING_POLICY_HH_

#include <memory>

namespace cute::data {

class SamplingPolicy {
public:
    SamplingPolicy();
    virtual ~SamplingPolicy();

    virtual bool accept(std::uint64_t timestamp, double* value) = 0;
};

}

#endif