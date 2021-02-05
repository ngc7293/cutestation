#include "widgets/control_widget.hh"

#include <assert.h>

#include <log/log.hh>

namespace cute::widgets {

ControlWidget::ControlWidget(QWidget* parent, const std::string& name)
    : Widget(parent, name)
{
}

ControlWidget::~ControlWidget() {}

// bool ControlWidget::init(const json& config)
// {
//     if (!Widget::init(config)) {
//         return false;
//     }

//     return true;
// }

} // namespaces