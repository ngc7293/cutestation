#include "data/series.h"

#include "policies/average_sampling_policy.h"

namespace cute { namespace data {

Series::Series(SamplingPolicySP sampling_policy)
    : sampling_policy_(sampling_policy)
{
}

Series::~Series() {}

}}