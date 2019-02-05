#include "ui/widgets/widget.hh"

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

Widget::Widget(QString name)
    : name_(name)
    , container_(new QWidget())
    , layout_(new QHBoxLayout(container_))
    , group_(new QGroupBox(name))
{
    container_->setMinimumHeight(200);
    layout_->setContentsMargins(0, 0, 0, 0);

    group_->setCheckable(true);
    group_->setLayout(new QVBoxLayout());
    QObject::connect(group_, SIGNAL(clicked(bool)), this, SLOT(onChecked(bool)));
    //group_->layout()->addWidget(container_);

    setLayout(new QVBoxLayout(this));
    ((QVBoxLayout*)layout())->addWidget(container_);
}

Widget::~Widget()
{
}

Widget& operator<<(Widget& widget, Message& message)
{
    widget.accept(message);
    return widget;
}

void Widget::onChecked(bool checked)
{
    container_->setVisible(checked);
    if (checked) {
        group_->layout()->addWidget(container_);
    } else {
        group_->layout()->removeWidget(container_);
    }
}

void Widget::setMinimumHeight(int minh)
{
    container_->setMinimumHeight(minh);
}