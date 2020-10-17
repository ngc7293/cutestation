#include "widgets/widget.h"

#include <QLayout>
#include <QTimer>

#include <data/series_factory.hh>

namespace cute::widgets {

Widget::Widget(QWidget* parent, const std::string& name)
    : QWidget(parent)
    , name_(name)
{
    setLayout(new QHBoxLayout(this));
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &Widget::refresh);
}

Widget::~Widget()
{
    timer_->stop();
    delete timer_;
}

void Widget::start(unsigned refreshRate)
{
    timer_->start(1000 / refreshRate);
}

} // namespaces