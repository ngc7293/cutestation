#include "widgets/widget_group.hh"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <log/log.hh>

namespace cute::widgets {

WidgetGroup::WidgetGroup(QWidget* parent, const std::string& name)
    : Widget(parent, name)
{
    box_ = new QGroupBox(QString::fromStdString(name), this);

    grid_ = new QGridLayout();
    box_->setLayout(grid_);
    layout()->addWidget(box_);
}

WidgetGroup::~WidgetGroup()
{
}

void WidgetGroup::set_name(const std::string& name)
{
    Widget::set_name(name);
    box_->setTitle(QString::fromStdString(name));
}

}