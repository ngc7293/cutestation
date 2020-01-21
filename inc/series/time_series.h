#ifndef TIME_SERIES_H_
#define TIME_SERIES_H_

#include "series.h"

#include <deque>
#include <utility>

class TimeSeries : public Series {
    Q_OBJECT

private:
    std::deque<std::pair<std::uint64_t, float>> data_;

public:
    TimeSeries();
    ~TimeSeries();

    void accept(const PacketSP) override;
    float last() override { return data_.size() ? data_.back().second : 0; }
};

#endif