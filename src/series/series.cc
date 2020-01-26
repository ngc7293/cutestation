#include "series/series.h"

#include "policies/average_sampling_policy.h"

Series::Series()
{
    sampling_policy_ = std::make_shared<AverageSamplingPolicy>(20);
}

Series::~Series() {}