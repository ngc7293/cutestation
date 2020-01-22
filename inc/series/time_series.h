#ifndef TIME_SERIES_H_
#define TIME_SERIES_H_

#include "series.h"

#include <deque>
#include <memory>
#include <mutex>
#include <utility>

#include <QPointF>
#include <QVector>

class TimeSeries;
typedef std::shared_ptr<TimeSeries> TimeSeriesSP;

class TimeSeries : public Series {
    Q_OBJECT

private:
    std::deque<std::pair<std::uint64_t, float>> data_;
    std::mutex mutex_;

public:
    TimeSeries();
    ~TimeSeries();

    void accept(const PacketSP) override;
    void toQVector(QVector<QPointF>& vector);
};

#endif