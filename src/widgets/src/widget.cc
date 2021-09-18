#include "widgets/widget.hh"

#include <QLayout>
#include <QTimer>

#include <data/series_factory.hh>

namespace cute::widgets {

Widget::Widget(QWidget* parent, const std::string& name)
    : QWidget(parent)
    , name_(name)
{
    setLayout(new QHBoxLayout(this));
}

Widget::~Widget() = default;

} // namespaces