#include "widgets/chart_widget.h"

#include <QLayout>
#include <QLineSeries>
#include <QValueAxis>

#include "series/time_series.h"

ChartWidget::ChartWidget(QWidget* parent, std::string name)
    : Widget(parent, name)
{
}

ChartWidget::~ChartWidget() {}

void ChartWidget::init(SeriesSP series)
{
    Widget::init(series);

    chartview_ = new QtCharts::QChartView(this);

    QtCharts::QLineSeries* lineseries = new QtCharts::QLineSeries(chartview_);
    lineseries->setUseOpenGL(true);

    QtCharts::QValueAxis* xaxis = new QtCharts::QValueAxis(chartview_);
    xaxis->setRange(-2, 2);

    QtCharts::QValueAxis* yaxis = new QtCharts::QValueAxis(chartview_);

    chartview_->chart()->addSeries(lineseries);
    chartview_->chart()->addAxis(xaxis, Qt::AlignBottom);
    chartview_->chart()->addAxis(yaxis, Qt::AlignLeft);

    lineseries->attachAxis(xaxis);
    lineseries->attachAxis(yaxis);

    layout()->addWidget(chartview_);
}

void ChartWidget::refresh()
{
    QVector<QPointF> data;
    std::dynamic_pointer_cast<TimeSeries>(series_)->toQVector(data);
}
