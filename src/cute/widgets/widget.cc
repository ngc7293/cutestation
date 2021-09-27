#include <QLayout>
#include <QTimer>

#include <cute/data/series_factory.hh>
#include <cute/widgets/widget.hh>

namespace cute::widgets {

Widget::Widget(QWidget* parent, const std::string& name)
    : QWidget(parent)
    , name_(name)
{
    setLayout(new QHBoxLayout(this));
}

Widget::~Widget() = default;

} // namespaces