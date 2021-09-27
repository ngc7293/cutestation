#include "view_widget.hh"

namespace cute::widgets {

ViewWidget::ViewWidget(QWidget* parent, const std::string& name)
    : Widget(parent, name)
{
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &ViewWidget::refresh);
}

ViewWidget::~ViewWidget()
{
    timer_->stop();
    delete timer_;
}


void ViewWidget::start(unsigned refreshRate)
{
    timer_->start(1000 / refreshRate);
}

}