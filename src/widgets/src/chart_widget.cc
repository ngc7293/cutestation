#include "widgets/chart_widget.hh"

#include <QApplication>
#include <QColor>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLayout>
#include <QLineSeries>
#include <QValueAxis>

#include <data/time_series.hh>
#include <util/time.hh>

namespace cute::widgets {

struct ChartWidget::ChartWidgetPriv {
    QtCharts::QChartView* chartview;
    double min, max;
    int length;
 
    std::vector<std::pair<QtCharts::QLineSeries*, std::shared_ptr<data::TimeSeries<double>>>> series;
    std::uint64_t last_update;
};

ChartWidget::ChartWidget(QWidget* parent, const std::string& name)
    : ViewWidget(parent, name)
    , _d(new ChartWidgetPriv)
{
    _d->length = 1;
    _d->min = 0;
    _d->max = 1;

    _d->last_update = 0;
    _d->chartview = new QtCharts::QChartView(this);

    QtCharts::QValueAxis* yaxis = new QtCharts::QValueAxis(_d->chartview);
    yaxis->setRange(_d->min, _d->max);

    QtCharts::QDateTimeAxis* xaxis = new QtCharts::QDateTimeAxis(_d->chartview);
    xaxis->setTickCount(2);

    _d->chartview->chart()->addAxis(xaxis, Qt::AlignBottom);
    _d->chartview->chart()->addAxis(yaxis, Qt::AlignLeft);

    // UI tweaks
    _d->chartview->setRenderHint(QPainter::Antialiasing);

    layout()->addWidget(_d->chartview);
}

ChartWidget::~ChartWidget() {}

void ChartWidget::add_series(std::shared_ptr<data::TimeSeries<double>> series)
{
    QtCharts::QLineSeries* lineseries = new QtCharts::QLineSeries(_d->chartview);
    _d->chartview->chart()->addSeries(lineseries);
    lineseries->setUseOpenGL(true);
    lineseries->attachAxis(_d->chartview->chart()->axes()[0]);
    lineseries->attachAxis(_d->chartview->chart()->axes()[1]);
    _d->series.emplace_back(lineseries, series);
}

void ChartWidget::set_length(unsigned length)
{
    _d->length = length;
}

void ChartWidget::set_range(double min, double max)
{
    _d->min = min;
    _d->max = max;
    ((QtCharts::QValueAxis*)_d->chartview->chart()->axes(Qt::Vertical)[0])->setRange(_d->min, _d->max);
}

void ChartWidget::refresh()
{
    for (auto& series: _d->series) {
        QVector<QPointF> points;
        series.second->data<QVector, QPointF>(points);

        if (points.size()) {
            auto now = util::now<std::milli>();
            series.first->replace(data);
            _d->last_update = std::max(_d->last_update, now);

            ((QtCharts::QDateTimeAxis*)_d->chartview->chart()->axes(Qt::Horizontal)[0])->setRange(QDateTime::fromMSecsSinceEpoch(_d->last_update - _d->length), QDateTime::fromMSecsSinceEpoch(_d->last_update));
        }
    }
}

} // namespaces