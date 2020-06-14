#include "widgets/button_widget.h"

#include <QLayout>

#include <log/log.h>
#include <util/util.h>

namespace cute::widgets {

ButtonWidget::ButtonWidget(QWidget* parent, const std::string& name)
    : ControlWidget(parent, name)
{
}

ButtonWidget::~ButtonWidget() {}

bool ButtonWidget::init(const json& config)
{
    if (!ControlWidget::init(config)) {
        return false;
    }

    button_ = new QPushButton(this);

    if (has<std::string>(config, "label")) {
        button_->setText(QString::fromStdString(config["label"].get<std::string>()));
    }

    layout()->addWidget(button_);
    connect(button_, &QPushButton::clicked, this, &ButtonWidget::clicked);
    return true;
}

void ButtonWidget::clicked()
{
    // command_->setValue(true);
}

void ButtonWidget::refresh()
{
    // button_->setEnabled(command_->hasRegisteredDataSources());
}

} // namespaces