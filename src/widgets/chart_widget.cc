#include "widgets/chart_widget.h"

#include <QColor>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLayout>
#include <QLineSeries>
#include <QValueAxis>

#include "data/time_series.h"
#include "log.h"
#include "util.h"

namespace cute { namespace widgets {

ChartWidget::ChartWidget(QWidget* parent, std::string name)
    : Widget(parent, name)
{
    last_update_ = 0;
}

ChartWidget::~ChartWidget() {}

bool ChartWidget::init(data::SeriesSP series, const json& config)
{
    Widget::init(series, config);

    if (!(timeseries_ = std::dynamic_pointer_cast<data::TimeSeries<double>>(series_))) {
        Log::err("ChartWidget", name_ + ": error obtaining TimeSeries");
        return false;
    }

    if (!has_uint(config, "length")) {
        Log::err("ChartWidget", name_ + ": missing or invalid configuration 'length'");
        return false;
    }
    length_ = config["length"].get<int>();

    if (!(has_array(config, "range", 2) && config["range"][0].is_number() && config["range"][1].is_number())) {
        Log::err("ChartWidget", name_ + ": missing or invalid configuration 'length'");
        return false;
    }
    min_ = std::min(config["range"][0].get<double>(), config["range"][1].get<double>());
    max_ = std::max(config["range"][0].get<double>(), config["range"][1].get<double>());

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
    chartview_->setRenderHint(QPainter::Antialiasing);

    lineseries->attachAxis(xaxis);
    lineseries->attachAxis(yaxis);

    layout()->addWidget(chartview_);

    return true;
}

void ChartWidget::refresh()
{
    QVector<QPointF> data;

    timeseries_->data<QVector, QPointF>(data);

    if (data.size() && data.back().x() > last_update_) {
        ((QtCharts::QLineSeries*)chartview_->chart()->series()[0])->replace(data);
        ((QtCharts::QDateTimeAxis*)chartview_->chart()->axes(Qt::Horizontal)[0])->setRange(QDateTime::fromMSecsSinceEpoch(now() - length_), QDateTime::fromMSecsSinceEpoch(now()));

        if (now() - data.back().x() > 10) {
            QPen pen(QRgb(0xff0000));
            pen.setWidth(2);
            ((QtCharts::QLineSeries*)chartview_->chart()->series()[0])->setPen(pen);
        } else {
            QPen pen(QRgb(0x0000ff));
            pen.setWidth(2);
            ((QtCharts::QLineSeries*)chartview_->chart()->series()[0])->setPen(pen);
        }

        last_update_ = now();
    }
}

}} // namespaces