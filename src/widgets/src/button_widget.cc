#include "widgets/button_widget.hh"

#include <QLayout>

namespace cute::widgets {

ButtonWidget::ButtonWidget(QWidget* parent, const std::string& name)
    : ControlWidget(parent, name)
{
}

ButtonWidget::~ButtonWidget() {}

// bool ButtonWidget::init(const json& config)
// {
//     series_ = data::SeriesFactory::build<bool>(config);
//     command_ = config["source"].get<std::string>();

//     if (!ControlWidget::init(config)) {
//         return false;
//     }

//     button_ = new QPushButton(this);

//     if (has<std::string>(config, "label")) {
//         button_->setText(QString::fromStdString(config["label"].get<std::string>()));
//     }

//     layout()->addWidget(button_);
//     connect(button_, &QPushButton::clicked, this, &ButtonWidget::clicked);
//     return true;
// }

void ButtonWidget::clicked()
{
    publish<bool>(command_, true);
}

void ButtonWidget::refresh()
{
    // button_->setEnabled(command_->hasRegisteredDataSources());
}

} // namespaces