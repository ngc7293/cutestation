#include "ui/sensorwidget.hh"

#include <QVBoxLayout>

#include <QChartView>
#include <QValueAxis>

using namespace QtCharts;

SensorWidget::SensorWidget(QString name)
    : name_(new QLabel(name, this))
    , value_(new QLabel("", this))
    , chart_(new QChart())
    , series_(new QLineSeries())
{
    count_ = 0;
    QValueAxis* valueAxis = new QValueAxis();
    valueAxis->setRange(0, 16);
    valueAxis->setTickCount(16);
    chart_->addSeries(series_);
    chart_->setAxisY(valueAxis, series_);
    chart_->legend()->setVisible(false);
    QHBoxLayout* hbox = new QHBoxLayout();
    QVBoxLayout* vbox = new QVBoxLayout();
    hbox->addWidget(name_);
    hbox->addWidget(value_, 1);
    vbox->addLayout(hbox);
    this->setLayout(new QHBoxLayout());
    ((QHBoxLayout* )this->layout())->addWidget(new QChartView(chart_), 1);
    ((QHBoxLayout* )this->layout())->addLayout(vbox);
}

SensorWidget::~SensorWidget()
{
}
