#ifndef SERIES_H_
#define SERIES_H_

#include <QObject>

#include <memory>

#include <nlohmann/json.hpp>

#include "proto/packet.h"
#include "policies/sampling_policy.h"

using json = nlohmann::json;

namespace cute { namespace data {

class Series : public QObject {
    Q_OBJECT

protected:
    SamplingPolicySP sampling_policy_;

public:
    Series();
    virtual ~Series();

    virtual bool init(SamplingPolicySP sampling_policy, const json& config);

    virtual void accept(const PacketSP) = 0;
};

using SeriesSP = std::shared_ptr<Series>;

}} // namespaces

#endif