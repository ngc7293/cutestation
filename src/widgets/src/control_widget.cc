#include "widgets/control_widget.h"

#include <assert.h>

#include <log/log.h>

namespace cute::widgets {

ControlWidget::ControlWidget(QWidget* parent, const std::string& name)
    : Widget(parent, name)
{
}

ControlWidget::~ControlWidget() {}

bool ControlWidget::init(const json& config)
{
    if (!Widget::init(config)) {
        return false;
    }

    return true;
}

} // namespaces