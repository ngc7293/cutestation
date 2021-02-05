#ifndef CUTE_DATA_SERIES_HH_
#define CUTE_DATA_SERIES_HH_

#include <memory>

#include <topic/subscriber.hh>

#include "sampling_policy.hh"

namespace cute::data {

class Series : public topic::Subscriber {
protected:
    std::shared_ptr<SamplingPolicy> sampling_policy_;

public:
    Series();
    virtual ~Series();
};

}

#endif