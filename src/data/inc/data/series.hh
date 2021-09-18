#ifndef CUTE_DATA_SERIES_HH_
#define CUTE_DATA_SERIES_HH_

#include <memory>

#include <topic/subscriber.hh>

#include "sampling_policy.hh"

namespace cute::data {

class Series {
protected:
    std::shared_ptr<SamplingPolicy> sampling_policy_;

public:
    Series() = default;
    virtual ~Series() = default;
};

}

#endif