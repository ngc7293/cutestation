#ifndef CUTE_WIDGETS_CHART_WIDGET_H_
#define CUTE_WIDGETS_CHART_WIDGET_H_

#include "view_widget.hh"

#include <QChartView>

#include <data/time_series.hh>

namespace cute::widgets {

class ChartWidget : public ViewWidget {
    Q_OBJECT

private:
    QtCharts::QChartView* chartview_;
    double min_, max_;
    int length_;
 
    std::shared_ptr<data::TimeSeries<double>> series_;
    std::uint64_t last_update_;

public:
    ChartWidget(QWidget* parent, const std::string& name);
    ~ChartWidget() override;

    void set_series(std::shared_ptr<data::TimeSeries<double>> series);
    void set_range(double min, double max);
    void set_length(unsigned length);

protected slots:
    void refresh() override;
};

} // namespaces

#endif