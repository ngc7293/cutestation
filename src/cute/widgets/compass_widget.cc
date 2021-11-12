#include "compass_widget.hh"

#include <QPainter>

#include <log/log.hh>
#include <util/geo.hh>

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
    int sr = _d -> radius * scale;

    QPainter painter(this);
    painter.setRenderHints({QPainter::Antialiasing, QPainter::TextAntialiasing});
    painter.translate(width() / 2, height() / 2);

    painter.save();
    painter.translate(0, -8);
    {
        painter.setPen(QColor(40, 40, 40));
        painter.drawEllipse(-sr, -sr, 2 * sr, 2 * sr);
        painter.drawEllipse(-sr / 2, -sr / 2, sr, sr);
        painter.drawLine(0, -sr, 0, sr);
        painter.drawLine(-sr, 0, sr, 0);
    }
    {
        for (int i = 0; i < 16; i++) {
            painter.save();
            painter.rotate((360.0 / 16.0) * i);
            painter.drawLine(0, -sr, 0, -sr + 4);
            painter.restore();
        }
    }

    {
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QColor(0, 0, 0));
        painter.setFont(QFont("Source Code Pro", 8));
        painter.drawText(QRect(0, sr, 0, 0),     (Qt::AlignHCenter | Qt::AlignTop | Qt::TextDontClip), QString::number(_d->radius, 'f', 0));
        painter.drawText(QRect(0, sr / 2, 0, 0), (Qt::AlignHCenter | Qt::AlignTop | Qt::TextDontClip), QString::number(_d->radius / 2, 'f', 0));
    }
    painter.restore();

    {
        util::geo::point from = {_d->reference.first->value(), _d->reference.second->value()};
        util::geo::point to = {_d->target.first->value(), _d->target.second->value()};

        double bearing = util::geo::bearing(from, to);
        double distance = util::geo::distance(from, to);
        int sd = static_cast<int>(distance * scale);

        painter.save();
        painter.translate(0, -8);
        painter.rotate(bearing);

        painter.setBrush(QColor(255, 0, 0));
        painter.setPen(Qt::NoPen);
        if (sd > sr) {
            painter.drawPolygon(QPolygon({
                {0, -sr}, {-6, -sr + 12}, {0, -sr + 9}, {6, -sr + 12}
            }));
        } else {
            painter.drawEllipse({0, -sd}, 4, 4);
        }
        painter.restore();

        painter.setBrush(Qt::NoBrush);
        painter.setPen(QColor(0, 0, 0));
        painter.drawText(QRect(-sr - 8, sr + 8, 0, 0), (Qt::AlignLeft  | Qt::AlignBottom | Qt::TextDontClip), QString("%1°").arg(bearing, 0, 'f', 2));
        painter.drawText(QRect( sr + 8, sr + 8, 0, 0), (Qt::AlignRight | Qt::AlignBottom | Qt::TextDontClip), QString("%1m").arg(distance, 0, 'f', 2));
    }
}

void CompassWidget::refresh()
{
    repaint();
}

}