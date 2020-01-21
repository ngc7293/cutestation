#ifndef SERIES_H_
#define SERIES_H_

#include <QObject>

#include "proto/packet.h"

#include "policies/sampling_policy.h"

class Series : public QObject {
    Q_OBJECT

protected:
    SamplingPolicy* sampling_policy_;

public:
    Series();
    ~Series();

    virtual void accept(const PacketSP) = 0;
    virtual float last() = 0;
};

#endif