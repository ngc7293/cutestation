#include "ui/widgets/accelerationwidget.hh"

#include <ctime>

#include <QChartView>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QSplineSeries>

#include "messages/accelerationmessage.hh"
#include "messages/message_defs.h"

using namespace QtCharts;

AccelerationWidget::AccelerationWidget()
    : SensorWidget("Acceleration")
{
    seriesX_ = new QSplineSeries();
    seriesX_->setName("x");
    seriesY_ = new QSplineSeries();
    seriesY_->setName("y");
    seriesZ_ = new QSplineSeries();
    seriesZ_->setName("z");
    seriesNorm_ = new QSplineSeries();
    seriesNorm_->setName("Norme");

    chart_ = new QChart();
    chart_->addSeries(seriesX_);
    chart_->addSeries(seriesY_);
    chart_->addSeries(seriesZ_);
    chart_->addSeries(seriesNorm_);
    chart_->legend()->setAlignment(Qt::AlignRight);

    max_ = 0;
    min_ = 0;

    axisX = new QDateTimeAxis();
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch() - GRAPH_LENGTH_SEC * 1000), QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch()));
    axisX->setFormat("HH:mm:ss");
    axisX->setTickCount(6);
    axisY = new QValueAxis();
    axisY->setRange(-10, 10);

    chart_->setAxisX(axisX, seriesX_);
    chart_->setAxisX(axisX, seriesY_);
    chart_->setAxisX(axisX, seriesZ_);
    chart_->setAxisX(axisX, seriesNorm_);
    chart_->setAxisY(axisY, seriesX_);
    chart_->setAxisY(axisY, seriesY_);
    chart_->setAxisY(axisY, seriesZ_);
    chart_->setAxisY(axisY, seriesNorm_);

    peak_ = new QLabel("");
    current_ = new QLabel("");
    peak_->setMinimumWidth(100);
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(new QLabel("<span style=\"font-weight: bold;\">PEAK</span>"));
    vbox->addWidget(peak_);
    vbox->addWidget(new QLabel("<span style=\"font-weight: bold;\">CURRENT</span>"));
    vbox->addWidget(current_);
    vbox->addStretch();
    layout_->addWidget(new QChartView(chart_), 1);
    layout_->addLayout(vbox);
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

    current_->setText(QString("%1m/s²").arg(msg.norm(), 0, 'f', 2));
    if (msg.norm() > max_) {
        max_ = msg.norm();
        peak_->setText(QString("%1m/s²").arg(msg.norm(), 0, 'f', 2));

        if (max_ > axisY->max()) {
            axisY->setMax(max_);
        }
    }

    if (min_ > msg.norm()) {
        min_ = msg.norm();

        if (min_ < axisY->min()) {
            axisY->setMin(min_);
        }
    }

    valuesX_.push_back(QPointF(now, msg.x()));
    valuesY_.push_back(QPointF(now, msg.y()));
    valuesZ_.push_back(QPointF(now, msg.z()));
    valuesNorm_.push_back(QPointF(now, msg.norm()));

    if (valuesNorm_.size() > 2) {
        while (valuesNorm_.last().x() - valuesNorm_.at(1).x() >= GRAPH_LENGTH_SEC * 1000) {
            valuesX_.removeFirst();
            valuesY_.removeFirst();
            valuesZ_.removeFirst();
            valuesNorm_.removeFirst();
        }
    }

    seriesX_->replace(valuesX_);
    seriesY_->replace(valuesY_);
    seriesZ_->replace(valuesZ_);
    seriesNorm_->replace(valuesNorm_);

    axisX->setRange(QDateTime::fromMSecsSinceEpoch(valuesNorm_.last().x() - GRAPH_LENGTH_SEC * 1000), QDateTime::fromMSecsSinceEpoch(valuesNorm_.last().x()));
}