#ifndef WIDGET_GROUP_HH_
#define WIDGET_GROUP_HH_

#include "widget.hh"

#include <string>

#include <QGroupBox>
#include <QGridLayout>

#include <log/log.hh>

namespace cute::widgets {

class WidgetGroup : public Widget {
private:
    QGroupBox* box_;
    QGridLayout* grid_;

public:
    WidgetGroup(QWidget* parent = nullptr, const std::string& name = "");
    virtual ~WidgetGroup();

    QGridLayout* grid() { return grid_; }

    void set_name(const std::string& name);

    void refresh() override { };
};

}

#endif