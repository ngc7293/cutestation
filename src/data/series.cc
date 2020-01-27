#include "data/series.h"

#include "policies/average_sampling_policy.h"

namespace cute { namespace data {

Series::Series()
{
    sampling_policy_ = std::make_shared<AverageSamplingPolicy>(20);
}

Series::~Series() {}

}}