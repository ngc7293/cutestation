#include "data/time_series.h"

#include <string>

#include "proto/packet.h"
#include "util.h"

#include "log.h"

namespace cute { namespace data {

TimeSeries::TimeSeries(SamplingPolicySP sampling_policy)
    : Series(sampling_policy)
{
}

TimeSeries::~TimeSeries() {}

void TimeSeries::accept(const PacketSP packet)
{
    double value = packet->value();
    if (sampling_policy_->accept(packet->timestamp(), &value)) {
        const std::lock_guard<std::mutex> lock(mutex_);
        data_.push_back(std::make_pair(packet->timestamp(), value));

        // TODO: Configurable data retention policy
        // retention_policy.execute()
        if (data_.size() > 10 && now() - data_.at(10).first > 5 * 1000) {
            data_.erase(data_.begin(), data_.begin() + 10);
        }
    }
}

void TimeSeries::toQVector(QVector<QPointF>& vector)
{
    const std::lock_guard<std::mutex> lock(mutex_);
    vector.reserve(data_.size());

    for (const auto& point : data_) {
        vector.push_back(QPointF(point.first, point.second));
    }
}

}} // namespaces