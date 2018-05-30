#include "ui/widgets/velocitywidget.hh"

#include <ctime>

#include <QChartView>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLabel>
#include <QSplineSeries>

#include "messages/altimetermessage.hh"
#include "messages/message_defs.h"

using namespace QtCharts;

VelocityWidget::VelocityWidget()
    : SensorWidget("Velocity")
{
    series_ = new QSplineSeries();
    series_->setName("AGL");

    max_ = 0;
    min_ = 0;

    chart_ = new QChart();
    chart_->addSeries(series_);
    chart_->legend()->setVisible(false);

    axisX = new QDateTimeAxis();
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch() - GRAPH_LENGTH_SEC * 1000), QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch()));
    axisX->setFormat("HH:mm:ss");
    axisX->setTickCount(6);
    axisY = new QValueAxis();
    axisY->setRange(0, 1);

    chart_->setAxisX(axisX, series_);
    chart_->setAxisY(axisY, series_);

    apogee_ = new QLabel("");
    current_ = new QLabel("");
    apogee_->setMinimumWidth(100);

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(new QLabel("<span style=\"font-weight: bold;\">PEAK</span>"));
    vbox->addWidget(apogee_);
    vbox->addWidget(new QLabel("<span style=\"font-weight: bold;\">CURRENT</span>"));
    vbox->addWidget(current_);
    vbox->addStretch();

    layout_->addWidget(new QChartView(chart_), 1);
    layout_->addLayout(vbox);
}

VelocityWidget::~VelocityWidget()
{
}

void VelocityWidget::accept(Message& message)
{
    if (message.id() != MSG_ID_ALTIMETER_DATA) {
        return;
    }

    AltimeterMessage& msg = (AltimeterMessage&)message;

    qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();

    current_->setText(QString("%1m/s").arg(msg.velocity(), 0, 'f', 2));
    if (max_ < msg.velocity()) {
        max_ = msg.velocity();
        apogee_->setText(QString("%1m/s").arg(max_, 0, 'f', 2));

        if (max_ > axisY->max()) {
            axisY->setMax(max_);
        }
    }

    if (min_ > msg.velocity()) {
        min_ = msg.velocity();

        if (min_ < axisY->min()) {
            axisY->setMin(min_);
        }
    }

    values_.push_back(QPointF(now, msg.velocity()));

    if (values_.size() > 2) {
        while (values_.last().x() - values_.at(1).x() >= GRAPH_LENGTH_SEC * 1000) {
            values_.removeFirst();
        }
    }

    series_->replace(values_);
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(values_.last().x() - GRAPH_LENGTH_SEC * 1000), QDateTime::fromMSecsSinceEpoch(values_.last().x()));
}