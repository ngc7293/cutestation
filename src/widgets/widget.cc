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

Widget::~Widget() {}

void Widget::init(SeriesSP series)
{
    series_ = series;

    setLayout(new QHBoxLayout(this));
}