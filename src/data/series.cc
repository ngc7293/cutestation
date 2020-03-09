#include "data/series.h"

#include "policies/average_sampling_policy.h"

namespace cute::data {

Series::Series()
{
}

Series::~Series() {}

bool Series::init(SamplingPolicySP sampling_policy, const json& config)
{
    sampling_policy_ = sampling_policy;
    return true;
}

} // namespaces