#ifndef CUTE_WIDGETS_WIDGET_GRID_HH_
#define CUTE_WIDGETS_WIDGET_GRID_HH_

#include <QGridLayout>

#include "widget.hh"

namespace cute::widgets {

class WidgetGrid : public QGridLayout {
    Q_OBJECT

public:
    WidgetGrid(QWidget* parent = nullptr);
    virtual ~WidgetGrid();

    void addWidget(Widget* widget, int x, int y, int xspan, int yspan);
};

}

#endif