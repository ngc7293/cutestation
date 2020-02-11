#include "widgets/single_value_widget.h"

#include <QLayout>

#include "log.h"

namespace cute { namespace widgets {

SingleValueWidget::SingleValueWidget(QWidget* parent, std::string name)
    : Widget(parent, name)
{
}

SingleValueWidget::~SingleValueWidget() {}

bool SingleValueWidget::init(data::SeriesSP series, const json& config)
{
    if (!Widget::init(series, config)) {
        return false;
    }

    if (!(timeseries_ = std::dynamic_pointer_cast<data::TimeSeries<double>>(series_))) {
        Log::err("SingleValueWidget", "Could not init widget " + name_ + ": error obtaining TimeSeries");
        return false;
    }

    if (!(config.count("format") && config["format"].is_string())) {
        Log::warn("SingleValueWidget", "Missing or invalid mandatory configuration 'format'");
        return false;
    }
    format_ = config["format"].get<std::string>();

    label_ = new QLabel(QString(format_.c_str()).arg(0));
    layout()->addWidget(label_);
    return true;
}

void SingleValueWidget::refresh()
{
    if (timeseries_->size() > 0) {
        label_->setText(QString(format_.c_str()).arg(timeseries_->last()));
    }
}

}} // namespaces