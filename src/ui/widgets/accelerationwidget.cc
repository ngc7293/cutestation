#include "ui/widgets/accelerationwidget.hh"

#include <ctime>

#include <QChartView>
#include <QDateTime>
#include <QDateTimeAxis>

#include "messages/message_defs.h"
#include "messages/accelerationmessage.hh"

AccelerationWidget::AccelerationWidget() : SensorWidget("Acceleration")
{
    seriesX_ = new QLineSeries();
    seriesX_->setName("x");
    seriesY_ = new QLineSeries();
    seriesY_->setName("y");
    seriesZ_ = new QLineSeries();
    seriesZ_->setName("z");
    seriesNorm_ = new QLineSeries();
    seriesNorm_->setName("Norme");

    chart_ = new QChart();
    chart_->addSeries(seriesX_);
    chart_->addSeries(seriesY_);
    chart_->addSeries(seriesZ_);
    chart_->addSeries(seriesNorm_);
    chart_->legend()->setAlignment(Qt::AlignRight);

    axisX = new QDateTimeAxis();
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(0), QDateTime::fromMSecsSinceEpoch(1));
    axisX->setFormat("HH:mm:ss.zzz");
    axisX->setTickCount(6);
    axisY = new QValueAxis();
    axisY->setRange(0, 10);

    chart_->setAxisX(axisX, seriesX_);
    chart_->setAxisX(axisX, seriesY_);
    chart_->setAxisX(axisX, seriesZ_);
    chart_->setAxisX(axisX, seriesNorm_);
    chart_->setAxisY(axisY, seriesX_);
    chart_->setAxisY(axisY, seriesY_);
    chart_->setAxisY(axisY, seriesZ_);
    chart_->setAxisY(axisY, seriesNorm_);

    layout_->addWidget(new QChartView(chart_), 1);
}

AccelerationWidget::~AccelerationWidget()
{
}

void AccelerationWidget::accept(Message& message)
{
    if (message.id() != MSG_ID_ACCELERATION) {
        return;
    }

    AccelerationMessage& msg = (AccelerationMessage&)message;

    qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();

    if (msg.norm() > 20 * 9.8) {
        return;
    }

    valuesX_.push_back(QPointF(now, msg.x()));
    if (valuesX_.size() > MAX_DATA_POINTS) {
        valuesX_.removeFirst();
    }

    valuesY_.push_back(QPointF(now, msg.y()));
    if (valuesY_.size() > MAX_DATA_POINTS) {
        valuesY_.removeFirst();
    }

    valuesZ_.push_back(QPointF(now, msg.z()));
    if (valuesZ_.size() > MAX_DATA_POINTS) {
        valuesZ_.removeFirst();
    }

    valuesNorm_.push_back(QPointF(now, msg.norm()));
    if (valuesNorm_.size() > MAX_DATA_POINTS) {
        valuesNorm_.removeFirst();
    }

    seriesX_->replace(valuesX_);
    seriesY_->replace(valuesY_);
    seriesZ_->replace(valuesZ_);
    seriesNorm_->replace(valuesNorm_);

    axisX->setRange(QDateTime::fromMSecsSinceEpoch(valuesNorm_.first().x()), QDateTime::fromMSecsSinceEpoch(valuesNorm_.last().x()));
    axisY->setMax((axisY->max() > msg.norm() ? axisY->max() : msg.norm()));
}