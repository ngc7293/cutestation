#include "ui/widgets/sensorwidget.hh"

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

SensorWidget::SensorWidget(QString name)
    : name_(name)
    , layout_(new QHBoxLayout())
{
    setMinimumHeight(250);
    setLayout(new QVBoxLayout(this));
    QGroupBox* box = new QGroupBox(name);
    box->setCheckable(true);
    box->setLayout(layout_);

    QObject::connect(box, SIGNAL(clicked(bool)), this, SLOT(onChecked(bool)));

    ((QVBoxLayout*)layout())->addWidget(box);
}

SensorWidget::~SensorWidget()
{
}

SensorWidget& operator<<(SensorWidget& widget, Message& message)
{
    widget.accept(message);
    return widget;
}

void SensorWidget::onChecked(bool checked)
{
    setMinimumHeight(checked ? 250 : 50);
    setMaximumHeight(checked ? QWIDGETSIZE_MAX : 50);
}