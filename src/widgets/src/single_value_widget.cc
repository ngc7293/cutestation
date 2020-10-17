#include "widgets/single_value_widget.h"

#include <QLayout>

namespace cute::widgets {

SingleValueWidget::SingleValueWidget(QWidget* parent, const std::string& name)
    : Widget(parent, name)
{
}

SingleValueWidget::~SingleValueWidget() {}

// bool SingleValueWidget::init(const json& config)
// {
//     if (!Widget::init(config)) {
//         return false;
//     }

//     if (!(timeseries_ = std::dynamic_pointer_cast<data::TimeSeries<double>>(series_))) {
//         Log::err("SingleValueWidget", name_ + ": error obtaining TimeSeries");
//         return false;
//     }

//     if (!has<std::string>(config, "format")) {
//         Log::err("SingleValueWidget", name_ + ": missing or invalid mandatory configuration 'format'");
//         return false;
//     }
//     format_ = config["format"].get<std::string>();

//     label_ = new QLabel(QString::fromStdString(format_).arg(0));
//     layout()->addWidget(label_);
//     return true;
// }

void SingleValueWidget::refresh()
{
    if (timeseries_->size() > 0) {
        label_->setText(QString(format_.c_str()).arg(timeseries_->last()));
    }
}

} // namespaces