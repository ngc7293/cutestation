#include <QLayout>

#include <log/log.hh>

#include "button_widget.hh"

namespace cute::widgets {

ButtonWidget::ButtonWidget(QWidget* parent, const std::string& name)
    : ViewWidget(parent, name)
{
    command_ = "";
    button_ = new QPushButton(this);
    button_->setText(QString::fromStdString(name));
    
    connect(button_, &QPushButton::clicked, this, &ButtonWidget::clicked);
    layout()->addWidget(button_);
}

ButtonWidget::~ButtonWidget() = default;

void ButtonWidget::set_command(const std::string& command)
{
    command_ = command;
}

void ButtonWidget::clicked()
{
    if (!publisher_.publish<int>(command_, 1)) {
        logging::warn("button") << logging::tag{"name", name_} << "Failed to publish command '" << command_ << "'" << logging::endl;
    } else {
        logging::debug("button") << logging::tag{"name", name_} << "Published command '" << command_ << "'" << logging::endl;
    }
}

void ButtonWidget::refresh()
{
}

} // namespaces