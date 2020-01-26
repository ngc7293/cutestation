#include "widgets/widget.h"

#include <QLayout>
#include <QTimer>

#include "series/time_series.h"
#include "util.h"

Widget::Widget(QWidget* parent, std::string name)
    : QWidget(parent)
    , name_(name)
{
}

Widget::~Widget()
{
    timer_->stop();
    delete timer_;
}

bool Widget::init(SeriesSP series, const json& config)
{
    if (!series) {
        return false;
    }

    series_ = series;
    setLayout(new QHBoxLayout(this));

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &Widget::refresh);

    if (config.count("refresh_rate") && config["refresh_rate"].is_number()) {
        timer_->start(1000 / config["refresh_rate"].get<int>());
    } else {
        return false;
    }

    return true;
}