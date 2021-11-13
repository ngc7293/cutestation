#ifndef CUTE_WIDGETS_SPACERWIDGET_HH_
#define CUTE_WIDGETS_SPACERWIDGET_HH_

#include "widget.hh"

#include <QProcessEnvironment>
#include <QPainter>

namespace cute::widgets {

class SpacerWidget: public Widget {
public:
    SpacerWidget(QWidget* parent)
        : Widget(parent, "")
    {
    }

    ~SpacerWidget() override
    {
    }

#if (not NDEBUG)
    void paintEvent(QPaintEvent *event) override
    {
        if (QProcessEnvironment::systemEnvironment().value("CUTE_DEBUG_LAYOUT", "0") == "1") {
            QPainter painter(this);
            painter.setBrush(QBrush(QColor(x() % 255, (width() * height()) % 255, y() % 255), Qt::BDiagPattern));
            painter.drawRect(rect());
        }
    }
#endif

};

}

#endif