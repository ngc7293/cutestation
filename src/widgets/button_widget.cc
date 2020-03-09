#include "widgets/button_widget.h"

#include <QLayout>

#include "log.h"

namespace cute::widgets {

ButtonWidget::ButtonWidget(QWidget* parent, std::string name)
    : ControlWidget(parent, name)
{
}

ButtonWidget::~ButtonWidget() {}

bool ButtonWidget::init(data::SeriesSP series, data::CommandSP command, const json& config)
{
    if (!ControlWidget::init(series, command, config)) {
        return false;
    }

    button_ = new QPushButton(this);
    layout()->addWidget(button_);
    connect(button_, &QPushButton::clicked, this, &ButtonWidget::clicked);
    return true;
}

void ButtonWidget::clicked()
{
    Log::info("ButtonWidget") << "Clicked!" << std::endl;
}

void ButtonWidget::refresh()
{
    button_->setEnabled(command_->ingestor() != nullptr);
}

} // namespaces