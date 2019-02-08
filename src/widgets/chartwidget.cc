#include "widgets/chartwidget.hh"

#include <iostream>

#include <ctime>

#include <QChartView>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLabel>
#include <QSplineSeries>
#include <QLineSeries>
#include <QGraphicsLayout>

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

    series_ = new QLineSeries();
    series_->setName("AGL");
    series_->setUseOpenGL(true);

    chart_ = new QChart();
    chart_->addSeries(series_);
    chart_->legend()->setVisible(false);
    chart_->layout()->setContentsMargins(0,0,0,0);
    chart_->setBackgroundVisible(false);

    axisX = new QDateTimeAxis();
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch() - graph_length_ * 1000), QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch()));
    axisX->setFormat("HH:mm:ss");
    axisX->setTickCount(6);
    axisY = new QValueAxis();
    axisY->setRange(min_, max_);

    chart_->addAxis(axisX, Qt::AlignBottom);
    chart_->addAxis(axisY, Qt::AlignLeft);
    series_->attachAxis(axisX);
    series_->attachAxis(axisY);

    QChartView* view = new QChartView(chart_);
    view->setRenderHint(QPainter::Antialiasing);
    layout_->addWidget(view, 1);

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &ChartWidget::refresh);
    timer_->start(50);
}

ChartWidget::~ChartWidget()
{
}

void ChartWidget::accept(Message& message)
{
    if ((*message.value())["name"] == value_.toStdString().c_str()) {
        qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();
        int value = (int)((*message.value())["value"].GetFloat());

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
    else {
        std::cout << (*message.value())["name"].GetString() << " != " << value_.toStdString() << std::endl;
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