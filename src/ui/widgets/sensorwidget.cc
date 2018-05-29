#include "ui/widgets/sensorwidget.hh"

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

SensorWidget::SensorWidget(QString name)
    : name_(name)
    , container_(new QWidget())
    , layout_(new QHBoxLayout(container_))
    , group_(new QGroupBox(name))
{
    container_->setMinimumHeight(200);

    group_->setCheckable(true);
    group_->setLayout(new QVBoxLayout());
    QObject::connect(group_, SIGNAL(clicked(bool)), this, SLOT(onChecked(bool)));
    group_->layout()->addWidget(container_);

    setLayout(new QVBoxLayout(this));
    ((QVBoxLayout*)layout())->addWidget(group_);
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
    container_->setVisible(checked);
    if (checked) {
        group_->layout()->addWidget(container_);
    } else {
        group_->layout()->removeWidget(container_);
    }
}

void SensorWidget::setMinimumHeight(int minh) {
    container_->setMinimumHeight(minh);
}