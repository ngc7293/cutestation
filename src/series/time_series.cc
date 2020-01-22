#include "series/time_series.h"

#include "proto/packet.h"
#include "util.h"

TimeSeries::TimeSeries() {}

TimeSeries::~TimeSeries() {}

void TimeSeries::accept(const PacketSP packet)
{
    float value = packet->value();
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

    int i = 0;
    for (const auto& point : data_) {
        vector << QPointF(point.first, point.second);
    }
}