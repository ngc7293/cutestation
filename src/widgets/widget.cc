#include "widgets/widget.hh"
#include "widgets/config/widget_config.hh"

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

Widget::Widget()
    : name_(new QLabel("Widget"))
    , config_(new Widget::Config(this))
    , container_(new QWidget())
    , layout_(new QHBoxLayout(container_))
{
    container_->setMinimumHeight(250);
    layout_->setContentsMargins(0, 0, 0, 0);

    setLayout(new QVBoxLayout(this));
    ((QVBoxLayout*)layout())->addWidget(name_);
    ((QVBoxLayout*)layout())->addWidget(container_);
}

Widget::~Widget()
{
}