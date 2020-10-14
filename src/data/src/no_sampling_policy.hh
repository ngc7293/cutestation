#ifndef CUTE_DATA_NO_SAMPLING_POLICY_HH_
#define CUTE_DATA_NO_SAMPLING_POLICY_HH_

#include "data/sampling_policy.hh"

namespace cute::data {

class NoSamplingPolicy : public SamplingPolicy {
public:
    NoSamplingPolicy() {}
    ~NoSamplingPolicy() override {}

    bool accept(std::uint64_t timestamp, double* value) override { return true;}
};

}

#endif