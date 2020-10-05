#ifndef CHART_WIDGET_H_
#define CHART_WIDGET_H_

#include "widget.h"

#include <QChartView>

#include "data/time_series.h"

namespace cute::widgets {

class ChartWidget : public Widget {
    Q_OBJECT

private:
    QtCharts::QChartView* chartview_;
    double min_, max_;
    int length_;
 
    data::TimeSeriesSP<double> timeseries_;
    std::uint64_t last_update_;

public:
    ChartWidget(QWidget* parent, std::string name);
    ~ChartWidget() override;

    bool init(data::SeriesSP series, const json& config = json()) override;

protected slots:
    void refresh() override;
};

} // namespaces

#endif