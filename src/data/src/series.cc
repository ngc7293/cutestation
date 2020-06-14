#include "data/series.h"

#include "data/sampling_policy.h"

namespace cute::data {

Series::Series()
{
}

Series::~Series() {}

bool Series::init(std::shared_ptr<SamplingPolicy> sampling_policy, const json& config)
{
    sampling_policy_ = sampling_policy;
    return true;
}

} // namespaces