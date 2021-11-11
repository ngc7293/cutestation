#include "compass_widget.hh"

#include <QPainter>

#include <log/log.hh>

namespace cute::widgets {

struct CompassWidget::Priv {
    double radius = 0;

    ValuePair reference;
    ValuePair target;
};

CompassWidget::CompassWidget(QWidget* parent, const std::string& name)
    : ViewWidget(parent, name)
    , _d(new Priv)
{
    logging::debug("CompassWidget") << "Created" << logging::endl;
}

CompassWidget::~CompassWidget()
{
}

void CompassWidget::set_radius(double radius)
{
    _d -> radius = radius;
}

void CompassWidget::set_reference(ValuePair&& reference)
{
    _d -> reference = std::move(reference);
}

void CompassWidget::set_target(ValuePair&& target)
{
    _d -> target = std::move(target);
}

void CompassWidget::paintEvent(QPaintEvent* event)
{
#if (not NDEBUG)
    Widget::paintEvent(event);
#endif

    int side = std::min(width() - 16, height() - 16);
    double scale = static_cast<double>(side) / (2 * _d -> radius);
    double sr = _d -> radius * scale;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.setPen(QColor(0, 0, 0));
    painter.drawEllipse(- sr, -sr, 2 * sr, 2 * sr);
    painter.drawEllipse(- sr / 2, -sr / 2, sr, sr);
    painter.drawLine(0, -sr, 0, sr);
    painter.drawLine(-sr, 0, sr, 0);

    painter.setBrush(QColor(0, 0, 0));
    painter.drawEllipse(-2, -2, 4, 4);

    painter.setBrush(QBrush());
    painter.setFont(QFont("Source Code Pro", 8));
    painter.drawText(QPoint(0, -sr), QString::number(_d->radius, 'f', 0));
    painter.drawText(QPoint(0, -sr / 2), QString::number(_d->radius / 2, 'f', 0));
}

void CompassWidget::refresh()
{
    repaint();
}

}