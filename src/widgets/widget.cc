#include "widgets/widget.hh"

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

Widget::Widget(QString name)
    : name_(name)
    , container_(new QWidget())
    , layout_(new QHBoxLayout(container_))
{
    container_->setMinimumHeight(250);
    layout_->setContentsMargins(0, 0, 0, 0);

    setLayout(new QVBoxLayout(this));
    ((QVBoxLayout*)layout())->addWidget(new QLabel(name_));
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

void Widget::setMinimumHeight(int minh)
{
    container_->setMinimumHeight(minh);
}