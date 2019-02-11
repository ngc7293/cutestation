    #include "widgets/chartwidget.hh"

#include <iostream>

#include <ctime>

#include <QChartView>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QGraphicsLayout>
#include <QLabel>
#include <QLineSeries>
#include <QSplineSeries>

#include "messages/message.hh"
#include "widgets/config/chartwidget_config.hh"

using namespace QtCharts;

ChartWidget::ChartWidget()
    : Widget()
    , config_(new ChartWidget::Config(this))
{
    graph_length_ = 60;
    max_ = -0;
    min_ = 0;
 
    series_ = new QLineSeries(this);
    series_->setName("agl");
    series_->setUseOpenGL(true);

    chart_ = new QChart();
    chart_->setParent(this);
    chart_->addSeries(series_);
    chart_->legend()->setVisible(false);
    chart_->layout()->setContentsMargins(0, 0, 0, 0);
    chart_->setBackgroundVisible(false);

    axisX = new QDateTimeAxis(chart_);
    axisX->setRange(
        QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch() - graph_length_ * 1000),
        QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch()));
    axisX->setFormat("HH:mm:ss");
    axisX->setTickCount(6);

    axisY = new QValueAxis(chart_);
    axisY->setRange(min_, max_);

    chart_->addAxis(axisX, Qt::AlignBottom);
    chart_->addAxis(axisY, Qt::AlignLeft);

    series_->attachAxis(axisX);
    series_->attachAxis(axisY);

    view_ = new QChartView(chart_, this);
    view_->setRenderHint(QPainter::Antialiasing);
    layout_->addWidget(view_, 1);

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &ChartWidget::refresh);
    timer_->start(50);
}

ChartWidget::~ChartWidget()
{
}

void ChartWidget::accept(Message& message)
{
    if (message.value()["name"] == value_.toStdString().c_str()) {
        qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();
        float value = message.value()["value"].GetFloat();

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
        while (values_.last().x() - values_.at(1).x() >= graph_length_ * 1000) {
            values_.removeFirst();
        }
    }

    series_->replace(values_);
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(values_.last().x() - graph_length_ * 1000), QDateTime::fromMSecsSinceEpoch(values_.last().x()));
}