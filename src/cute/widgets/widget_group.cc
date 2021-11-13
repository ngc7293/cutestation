#include <QHBoxLayout>
#include <QVBoxLayout>

#include <cute/widgets/widget_group.hh>

namespace cute::widgets {

WidgetGroup::WidgetGroup(QWidget* parent, const std::string& name)
    : Widget(parent, name)
{
    box_ = new QGroupBox(QString::fromStdString(name), this);

    grid_ = new WidgetGrid();
    box_->setLayout(grid_);
    layout()->addWidget(box_);
    layout()->setContentsMargins(10, 10, 10, 10);
}

WidgetGroup::~WidgetGroup() = default;

void WidgetGroup::set_name(const std::string& name)
{
    Widget::set_name(name);
    box_->setTitle(QString::fromStdString(name));
}

}