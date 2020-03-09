#include "widgets/widget.h"

#include <QLayout>
#include <QTimer>

#include "data/time_series.h"
#include "log.h"
#include "util.h"

namespace cute::widgets {

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

bool Widget::init(data::SeriesSP series, const json& config)
{
    if (!series) {
        return false;
    }

    series_ = series;
    setLayout(new QHBoxLayout(this));

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &Widget::refresh);

    if (has_int(config, "refresh_rate")) {
        timer_->start(1000 / config["refresh_rate"].get<int>());
    } else {
        Log::err("Widget", name_ + ": missing or invalid mandatory configuration 'refresh_rate'");
        return false;
    }

    return true;
}

} // namespaces