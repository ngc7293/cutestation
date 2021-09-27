#ifndef CUTE_DATA_SAMPLINGPOLICY_HH_
#define CUTE_DATA_SAMPLINGPOLICY_HH_

#include <memory>

namespace cute::data {

class SamplingPolicy {
public:
    SamplingPolicy() = default;
    virtual ~SamplingPolicy() = default;

    virtual bool accept(std::uint64_t timestamp, double* value) = 0;
};

}

#endif