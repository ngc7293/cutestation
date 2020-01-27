#ifndef SERIES_H_
#define SERIES_H_

#include <QObject>

#include <memory>

#include "proto/packet.h"
#include "policies/sampling_policy.h"

namespace cute { namespace data {

class Series;
typedef std::shared_ptr<Series> SeriesSP;

class Series : public QObject {
    Q_OBJECT

protected:
    SamplingPolicySP sampling_policy_;

public:
    Series();
    ~Series();

    virtual void accept(const PacketSP) = 0;
};

}} // namespaces

#endif