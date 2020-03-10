#ifndef DATA_SERIES_H_
#define DATA_SERIES_H_

#include <QObject>

#include <memory>

#include <nlohmann/json.hpp>

#include "proto/packet.h"
#include "policies/sampling_policy.h"

using json = nlohmann::json;

namespace cute::data {

class Series : public QObject {
    Q_OBJECT

protected:
    SamplingPolicySP sampling_policy_;

public:
    Series();
    virtual ~Series();

    virtual bool init(SamplingPolicySP sampling_policy, const json& config);

    virtual void accept(const proto::Measurement& measurement) = 0;
};

using SeriesSP = std::shared_ptr<Series>;

} // namespaces

#endif