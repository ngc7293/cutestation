#include "compass_widget.hh"

#include <QPainter>

#include <log/log.hh>
#include <util/geo.hh>

namespace cute::widgets {

struct CompassWidget::Priv {
    double radius = 0;

    ValuePair reference;
    ValuePair target;

    void drawBackground(QPainter& painter, double scale);
    void drawTarget(QPainter& patiner, double scale);
};

CompassWidget::CompassWidget(QWidget* parent, const std::string& name)
    : ViewWidget(parent, name)
    , _d(new Priv)
{
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

    QPainter painter(this);
    painter.setRenderHints({QPainter::Antialiasing, QPainter::TextAntialiasing});
    painter.translate(width() / 2, height() / 2);
    painter.scale(scale, scale);

    _d -> drawBackground(painter, scale);
    _d -> drawTarget(painter, scale);
}

void CompassWidget::refresh()
{
    repaint();
}

void CompassWidget::Priv::drawBackground(QPainter& painter, double scale)
{
    painter.save();
    painter.translate(0, (-8 / scale));
    painter.setPen(QPen(QColor(40, 40, 40), 1 / scale));

    // Draw concentric circles and axes
    painter.drawEllipse(-radius, -radius, 2 * radius, 2 * radius);
    painter.drawEllipse(-radius / 2, -radius / 2, radius, radius);
    painter.drawLine(0, -radius, 0, radius);
    painter.drawLine(-radius, 0, radius, 0);

    // Draw minor tick marks
    for (int i = 0; i < 16; i++) {
        painter.save();
        painter.rotate((360.0 / 16.0) * i);
        painter.drawLine(0, -radius, 0, -radius + (4 / scale));
        painter.restore();
    }

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(0, 0, 0));
    painter.setFont(QFont("Source Code Pro", (8 / scale)));
    painter.drawText(QRect(0, radius, 0, 0),     (Qt::AlignHCenter | Qt::AlignTop | Qt::TextDontClip), QString::number(radius, 'f', 0));
    painter.drawText(QRect(0, radius / 2, 0, 0), (Qt::AlignHCenter | Qt::AlignTop | Qt::TextDontClip), QString::number(radius / 2, 'f', 0));

    painter.restore();
}

void CompassWidget::Priv::drawTarget(QPainter& painter, double scale)
{
    util::geo::point from = {reference.first->value(), reference.second->value()};
    util::geo::point to = {target.first->value(), target.second->value()};

    double bearing = util::geo::bearing(from, to);
    double distance = util::geo::distance(from, to);

    painter.save();
    painter.translate(0, (-8/scale));
    painter.rotate(bearing);

    painter.setBrush(QColor(255, 0, 0));
    painter.setPen(Qt::NoPen);
    if (distance > radius) {
        painter.drawPolygon(QPolygon({
            QPoint(0, -radius), QPoint(-6/scale, -radius + 12/scale), QPoint(0, -radius + 9/scale), QPoint(6/scale, -radius + 12/scale)
        }));
    } else {
        painter.drawEllipse({0, -distance}, 4/scale, 4/scale);
    }
    painter.restore();

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(0, 0, 0));
    painter.setFont(QFont("Source Code Pro", (12 / scale)));
    painter.drawText(QRect(-radius - 8/scale, radius + 8/scale, 0, 0), (Qt::AlignLeft  | Qt::AlignBottom | Qt::TextDontClip), QString("%1°").arg(bearing, 0, 'f', 2));
    painter.drawText(QRect( radius + 8/scale, radius + 8/scale, 0, 0), (Qt::AlignRight | Qt::AlignBottom | Qt::TextDontClip), QString("%1m").arg(distance, 0, 'f', 2));
}

}