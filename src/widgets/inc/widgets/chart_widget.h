#ifndef CUTE_WIDGETS_CHART_WIDGET_H_
#define CUTE_WIDGETS_CHART_WIDGET_H_

#include "widget.h"

#include <QChartView>

#include <data/time_series.hh>

namespace cute::widgets {

class ChartWidget : public Widget {
    Q_OBJECT

private:
    QtCharts::QChartView* chartview_;
    double min_, max_;
    int length_;
 
    std::shared_ptr<data::TimeSeries<double>> timeseries_;
    std::uint64_t last_update_;

public:
    ChartWidget(QWidget* parent, const std::string& name, std::shared_ptr<data::TimeSeries<double>> series, unsigned length, double min = -1, double max = -1);
    ~ChartWidget() override;

protected slots:
    void refresh() override;
};

} // namespaces

#endif