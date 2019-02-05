#include "ui/widgets/chartwidget.hh"

#include <ctime>

#include <QChartView>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLabel>
#include <QSplineSeries>
#include <QLineSeries>

#include "messages/message.hh"

using namespace QtCharts;

ChartWidget::ChartWidget()
    : Widget("Altitude")
{
    series_ = new QLineSeries();
    series_->setName("AGL");
    series_->setUseOpenGL(true);

    max_ = 200;
    min_ = 0;

    chart_ = new QChart();
    chart_->addSeries(series_);
    chart_->legend()->setVisible(false);

    axisX = new QDateTimeAxis();
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch() - GRAPH_LENGTH_SEC * 1000), QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch()));
    axisX->setFormat("HH:mm:ss");
    axisX->setTickCount(6);
    axisY = new QValueAxis();
    axisY->setRange(min_, max_);

    chart_->setAxisX(axisX, series_);
    chart_->setAxisY(axisY, series_);

    chart_->setBackgroundVisible(false);

    layout_->addWidget(new QChartView(chart_), 1);

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &ChartWidget::refresh);
    timer_->start(50);
}

ChartWidget::~ChartWidget()
{
}

void ChartWidget::accept(Message& message)
{
    if ((*message.value())["name"] == "altitude") {
        qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();
        int value = (*message.value())["value"].GetInt();

         if (max_ < value) {
            max_ = value;

            if (max_ > axisY->max()) {
                axisY->setMax(max_);
            }
        }
         if (min_ > value) {
            min_ = value;

            if (min_ < axisY->min()) {
                axisY->setMin(min_);
            }
        }

        values_.push_back(QPointF(now, value));
    }
}

void ChartWidget::refresh() 
{
    if (values_.size() > 2) {
        while (values_.last().x() - values_.at(1).x() >= GRAPH_LENGTH_SEC * 1000) {
            values_.removeFirst();
        }
    }

    series_->replace(values_);
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(values_.last().x() - GRAPH_LENGTH_SEC * 1000), QDateTime::fromMSecsSinceEpoch(values_.last().x()));
}