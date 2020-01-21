#include "series/series.h"

#include "policies/no_sampling_policy.h"

Series::Series()
{
    sampling_policy_ = new NoSamplingPolicy();
}

Series::~Series() {}