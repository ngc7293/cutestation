#include "widgets/widget.h"

#include <QLayout>
#include <QTimer>

Widget::Widget(QWidget* parent, std::string name)
    : QWidget(parent)
    , name_(name)
{
}

Widget::~Widget() {}

void Widget::init(Series* series)
{
    series_ = series;

    label_ = new QLabel(name_.c_str(), this);
    setLayout(new QHBoxLayout(this));
    layout()->addWidget(label_);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::refresh);
    timer->start(1000 / 30);
}

void Widget::refresh()
{
    label_->setText(QString("value: %1").arg(QString::number(series_->last())));
}