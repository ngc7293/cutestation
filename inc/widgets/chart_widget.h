#ifndef CHART_WIDGET_H_
#define CHART_WIDGET_H_

#include "widget.h"

#include <QChartView>

class ChartWidget : public Widget {
    Q_OBJECT

private:
    QtCharts::QChartView* chartview_;

public:
    ChartWidget(QWidget* parent, std::string name);
    ~ChartWidget() override;

    void init(SeriesSP series) override;

protected slots:
    void refresh() override;
};

#endif