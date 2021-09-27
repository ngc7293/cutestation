#ifndef CUTE_WIDGETS_CHARTWIDGET_H_
#define CUTE_WIDGETS_CHARTWIDGET_H_

#include <QChartView>

#include <cute/data/time_series.hh>

#include "view_widget.hh"

namespace cute::widgets {

class ChartWidget : public ViewWidget {
    Q_OBJECT
    struct Priv;

public:
    ChartWidget(QWidget* parent, const std::string& name);
    ~ChartWidget() override;

    void add_series(std::shared_ptr<data::TimeSeries> series);
    void set_range(double min, double max);
    void set_length(std::chrono::milliseconds length);

protected slots:
    void refresh() override;

private:
    std::unique_ptr<Priv> _d;
};

} // namespaces

#endif