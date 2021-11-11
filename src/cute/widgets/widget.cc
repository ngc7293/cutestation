#include <QLayout>
#include <QPainter>
#include <QProcessEnvironment>
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

#if (not NDEBUG)
void Widget::paintEvent(QPaintEvent *event)
{
    if (QProcessEnvironment::systemEnvironment().value("CUTE_DEBUG_LAYOUT", "0") == "1") {
        QPainter painter(this);
        painter.setBrush(QColor(x() % 255, (width() * height()) % 255, y() % 255));
        painter.drawRect(rect());
    }
}
#endif

} // namespaces