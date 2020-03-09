#include "widgets/control_widget.h"

#include <assert.h>

#include "log.h"

namespace cute::widgets {

ControlWidget::ControlWidget(QWidget* parent, std::string name)
    : Widget(parent, name)
{
}

ControlWidget::~ControlWidget() {}

bool ControlWidget::init(data::SeriesSP series, const json& config)
{
    Log::err("ControlWidget") << "ControlWidget::init called with no command paramter!" << std::endl;
    assert(false);
    return false;
}

bool ControlWidget::init(data::SeriesSP series, data::CommandSP command, const json& config)
{
    if (!Widget::init(series, config)) {
        return false;
    }

    command_ = command;
    return true;
}

} // namespaces