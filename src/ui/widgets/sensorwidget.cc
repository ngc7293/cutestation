#include "ui/widgets/sensorwidget.hh"

#include <QLabel>
#include <QVBoxLayout>

SensorWidget::SensorWidget(QString name)
    : name_(name)
    , layout_(new QHBoxLayout())
{
    setLayout(new QVBoxLayout(this));
    ((QVBoxLayout* )layout())->addWidget(new QLabel(name_));
    ((QVBoxLayout* )layout())->addLayout(layout_, 1);
}

SensorWidget::~SensorWidget()
{
}

SensorWidget& operator<<(SensorWidget& widget, Message& message)
{
    widget.accept(message);
}