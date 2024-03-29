#include <QApplication>
#include <QColor>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLayout>
#include <QLineSeries>
#include <QValueAxis>

#include <cute/data/time_series.hh>
#include <util/time.hh>

#include "chart_widget.hh"

using namespace std::literals::chrono_literals;

namespace cute::widgets {

struct ChartWidget::Priv {
    QChartView* chartview;
    double min, max;
    std::chrono::milliseconds length;
 
    std::vector<std::pair<QLineSeries*, std::shared_ptr<data::TimeSeries>>> series;
    std::chrono::milliseconds last_update;
};

ChartWidget::ChartWidget(QWidget* parent, const std::string& name)
    : ViewWidget(parent, name)
    , _d(new Priv)
{
    _d->length = 1ms;
    _d->min = 0;
    _d->max = 1;

    _d->last_update = 0ms;
    _d->chartview = new QChartView(this);

    QValueAxis* yaxis = new QValueAxis(_d->chartview);
    yaxis->setRange(_d->min, _d->max);

    QDateTimeAxis* xaxis = new QDateTimeAxis(_d->chartview);
    xaxis->setTickCount(5);
    xaxis->setFormat("HH:mm:ss");

    _d->chartview->chart()->addAxis(xaxis, Qt::AlignBottom);
    _d->chartview->chart()->addAxis(yaxis, Qt::AlignLeft);

    // UI tweaks
    _d->chartview->setRenderHint(QPainter::Antialiasing);
    _d->chartview->chart()->setBackgroundVisible(false);
    _d->chartview->chart()->setMargins(QMargins(0, 0, 0, 0));
    _d->chartview->chart()->legend()->hide();

    layout()->addWidget(_d->chartview);
}

ChartWidget::~ChartWidget() = default;

void ChartWidget::add_series(std::shared_ptr<data::TimeSeries> series)
{
    QLineSeries* lineseries = new QLineSeries(_d->chartview);
    _d->chartview->chart()->addSeries(lineseries);
    lineseries->setUseOpenGL(true);
    lineseries->attachAxis(_d->chartview->chart()->axes()[0]);
    lineseries->attachAxis(_d->chartview->chart()->axes()[1]);
    _d->series.emplace_back(lineseries, series);
}

void ChartWidget::set_length(std::chrono::milliseconds length)
{
    _d->length = length;
}

void ChartWidget::set_range(double min, double max)
{
    _d->min = min;
    _d->max = max;
    ((QValueAxis*)_d->chartview->chart()->axes(Qt::Vertical)[0])->setRange(_d->min, _d->max);
}

void ChartWidget::refresh()
{
    for (auto& series: _d->series) {
        QVector<QPointF> points;
        series.second->data<QVector, QPointF>(points);

        if (points.size()) {
            auto now = util::time::now<std::chrono::milliseconds>();
            series.first->replace(points);
            _d->last_update = std::max(_d->last_update, now);

            ((QDateTimeAxis*)_d->chartview->chart()->axes(Qt::Horizontal)[0])->setRange(QDateTime::fromMSecsSinceEpoch((_d->last_update - _d->length).count()), QDateTime::fromMSecsSinceEpoch(_d->last_update.count()));
        }
    }
}

} // namespaces