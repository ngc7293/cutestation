#ifndef CUTE_WIDGETS_CHART_WIDGET_H_
#define CUTE_WIDGETS_CHART_WIDGET_H_

#include "view_widget.hh"

#include <QChartView>

#include <data/time_series.hh>

namespace cute::widgets {

class ChartWidget : public ViewWidget {
    Q_OBJECT
    struct Priv;

public:
    ChartWidget(QWidget* parent, const std::string& name);
    ~ChartWidget() override;

    void add_series(std::shared_ptr<data::TimeSeries<double>> series);
    void set_range(double min, double max);
    void set_length(unsigned length);

protected slots:
    void refresh() override;

private:
    std::unique_ptr<Priv> _d;
};

} // namespaces

#endif