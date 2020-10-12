#ifndef DATA_SERIES_H_
#define DATA_SERIES_H_

#include <QObject>

#include <memory>

#include <nlohmann/json.hpp>

#include <topic/subscriber.hh>

#include "packet.pb.h"
#include "sampling_policy.h"

using json = nlohmann::json;

namespace cute::data {

class Series : public QObject, public topic::Subscriber {
    Q_OBJECT

protected:
    SamplingPolicySP sampling_policy_;

public:
    Series();
    virtual ~Series();

    virtual bool init(SamplingPolicySP sampling_policy, const json& config);
};

using SeriesSP = std::shared_ptr<Series>;

} // namespaces

#endif