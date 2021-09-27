#ifndef CUTE_WIDGETS_WIDGETGROUP_HH_
#define CUTE_WIDGETS_WIDGETGROUP_HH_

#include <string>

#include <QGroupBox>
#include <QGridLayout>

#include "widget.hh"
#include "widget_grid.hh"

namespace cute::widgets {

class WidgetGroup : public Widget {
    Q_OBJECT

private:
    QGroupBox* box_;
    WidgetGrid* grid_;

public:
    WidgetGroup(QWidget* parent = nullptr, const std::string& name = "");
    virtual ~WidgetGroup();

    WidgetGrid* grid() { return grid_; }

    void set_name(const std::string& name);
};

}

#endif