#include "ui/widgets/altitudewidget.hh"

#include <ctime>

#include <QChartView>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLabel>

#include "messages/altimetermessage.hh"
#include "messages/message_defs.h"

using namespace QtCharts;

AltitudeWidget::AltitudeWidget()
    : SensorWidget("Altitude")
{
    series_ = new QLineSeries();
    series_->setName("AGL");

    max_ = 0;
    min_ = -0;

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

AltitudeWidget::~AltitudeWidget()
{
}

void AltitudeWidget::accept(Message& message)
{
    if (message.id() != MSG_ID_ALTIMETER_DATA) {
        return;
    }

    AltimeterMessage& msg = (AltimeterMessage&)message;

    qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();

    current_->setText(QString("%1m").arg(msg.agl_altitude(), 0, 'f', 2));
    if (max_ < msg.agl_altitude()) {
        max_ = msg.agl_altitude();
        apogee_->setText(QString("%1m").arg(max_, 0, 'f', 2));
        axisY->setMax(max_);
    }

    if (min_ > msg.agl_altitude()) {
        min_ = msg.agl_altitude();
        axisY->setMin(min_);
    }

    values_.push_back(QPointF(now, msg.agl_altitude()));

    while (values_.last().x() - values_.first().x() > GRAPH_LENGTH_SEC * 1000) {
        values_.removeFirst();
    }

    series_->replace(values_);
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(values_.last().x() - GRAPH_LENGTH_SEC * 1000), QDateTime::fromMSecsSinceEpoch(values_.last().x()));
}