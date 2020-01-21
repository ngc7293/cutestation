#include "policies/no_sampling_policy.h"

NoSamplingPolicy::NoSamplingPolicy() {}

NoSamplingPolicy::~NoSamplingPolicy() {}

bool NoSamplingPolicy::accept(std::uint64_t timestamp, float* value)
{
    return true;
}
