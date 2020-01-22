#include "widgets/chart_widget.h"

#include <QColor>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLayout>
#include <QLineSeries>
#include <QValueAxis>

#include "series/time_series.h"
#include "util.h"

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

    QtCharts::QValueAxis* yaxis = new QtCharts::QValueAxis(chartview_);
    yaxis->setRange(-2, 2);

    QtCharts::QDateTimeAxis* xaxis = new QtCharts::QDateTimeAxis(chartview_);
    xaxis->setTickCount(2);

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

    if (data.size()) {
        ((QtCharts::QLineSeries*)chartview_->chart()->series()[0])->replace(data);
        ((QtCharts::QDateTimeAxis*)chartview_->chart()->axisX())->setRange(QDateTime::fromMSecsSinceEpoch(data.front().x()), QDateTime::fromMSecsSinceEpoch(data.back().x()));

        if (now() - data.back().x() > 10) {
            QPen pen(QRgb(0xff0000));
            pen.setWidth(2);
            ((QtCharts::QLineSeries*)chartview_->chart()->series()[0])->setPen(pen);
        } else {
            QPen pen(QRgb(0x0000ff));
            pen.setWidth(2);
            ((QtCharts::QLineSeries*)chartview_->chart()->series()[0])->setPen(pen);
        }
    }
}