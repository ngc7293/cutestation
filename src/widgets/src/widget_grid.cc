#include "widgets/widget_grid.hh"

namespace cute::widgets {

WidgetGrid::WidgetGrid(QWidget* parent)
    : QGridLayout(parent)
{
}

WidgetGrid::~WidgetGrid() = default;

void WidgetGrid::addWidget(Widget* widget, int x, int y, int xspan, int yspan)
{
    QGridLayout::addWidget((QWidget*) widget, y, x, yspan, xspan);   
}

}