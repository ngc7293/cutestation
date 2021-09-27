#ifndef CUTE_DATA_NOSAMPLINGPOLICY_HH_
#define CUTE_DATA_NOSAMPLINGPOLICY_HH_

#include <cute/data/sampling_policy.hh>

namespace cute::data {

class NoSamplingPolicy : public SamplingPolicy {
public:
    NoSamplingPolicy() = default;
    ~NoSamplingPolicy() override = default;

    bool accept(std::uint64_t timestamp, double* value) override { return true; }
};

}

#endif