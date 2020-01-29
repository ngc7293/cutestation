#ifndef CHART_WIDGET_H_
#define CHART_WIDGET_H_

#include "widget.h"

#include <QChartView>

namespace cute { namespace widgets {

class ChartWidget;
typedef std::shared_ptr<ChartWidget> ChartWidgetSP;

class ChartWidget : public Widget {
    Q_OBJECT

private:
    QtCharts::QChartView* chartview_;
    std::uint64_t last_update_;

public:
    ChartWidget(QWidget* parent, std::string name);
    ~ChartWidget() override;

    bool init(data::SeriesSP series, const json& config = json()) override;

protected slots:
    void refresh() override;
};

}} // namespaces

#endif