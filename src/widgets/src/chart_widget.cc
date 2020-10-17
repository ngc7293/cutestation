#include "widgets/chart_widget.h"

#include <QApplication>
#include <QColor>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLayout>
#include <QLineSeries>
#include <QValueAxis>

#include <data/time_series.hh>
#include <log/log.hh>
#include <util/time.hh>

namespace cute::widgets {

ChartWidget::ChartWidget(QWidget* parent, const std::string& name, std::shared_ptr<data::TimeSeries<double>> series, unsigned length, double min, double max)
    : Widget(parent, name)
{
    timeseries_ = series;
    length = length;
    min_ = min;
    max_ = max;

    last_update_ = 0;

    chartview_ = new QtCharts::QChartView(this);

    QtCharts::QLineSeries* lineseries = new QtCharts::QLineSeries(chartview_);
    lineseries->setUseOpenGL(true);

    QtCharts::QValueAxis* yaxis = new QtCharts::QValueAxis(chartview_);
    yaxis->setRange(min_, max_);

    QtCharts::QDateTimeAxis* xaxis = new QtCharts::QDateTimeAxis(chartview_);
    xaxis->setTickCount(2);

    chartview_->chart()->addSeries(lineseries);
    chartview_->chart()->addAxis(xaxis, Qt::AlignBottom);
    chartview_->chart()->addAxis(yaxis, Qt::AlignLeft);

    lineseries->attachAxis(xaxis);
    lineseries->attachAxis(yaxis);

    // UI tweaks
    chartview_->setRenderHint(QPainter::Antialiasing);

    layout()->addWidget(chartview_);
}

ChartWidget::~ChartWidget() {}

void ChartWidget::refresh()
{
    QVector<QPointF> data;

    timeseries_->data<QVector, QPointF>(data);
    // Log::debug("ChartWidget/" + name_) << "refresh(), data.size()=" << timeseries_->size() << std::endl;


    if (data.size()) {
        auto now = util::now<std::milli>();
        ((QtCharts::QLineSeries*)chartview_->chart()->series()[0])->replace(data);
        ((QtCharts::QDateTimeAxis*)chartview_->chart()->axes(Qt::Horizontal)[0])->setRange(QDateTime::fromMSecsSinceEpoch(now - 5000), QDateTime::fromMSecsSinceEpoch(now));

// #ifndef NDEBUG
//         if (now - data.back().x() > 10) {
//             QPen pen(QRgb(0xff0000));
//             pen.setWidth(2);
//             ((QtCharts::QLineSeries*)chartview_->chart()->series()[0])->setPen(pen);
//         } else {
//             QPen pen(QRgb(0x0000ff));
//             pen.setWidth(2);
//             ((QtCharts::QLineSeries*)chartview_->chart()->series()[0])->setPen(pen);
//         }
// #endif

        last_update_ = now;
    }
}

} // namespaces