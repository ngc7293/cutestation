#include "widgets/single_value_widget.hh"

#include <QLabel>
#include <QLayout>

#include <data/single_value.hh>

namespace cute::widgets {

struct SingleValueWidget::Priv {
    QLabel* label;
    std::unique_ptr<data::SingleValue<double>> value;
};

SingleValueWidget::SingleValueWidget(QWidget* parent, const std::string& name)
    : ViewWidget(parent, name)
    , _d(new Priv)
{
    _d -> label = new QLabel(QString::fromStdString(name), this);
    layout()->addWidget(_d -> label);
}

SingleValueWidget::~SingleValueWidget() { }

void SingleValueWidget::set_value(std::unique_ptr<data::SingleValue<double>>&& value)
{
    _d -> value = std::move(value);
}

void SingleValueWidget::refresh()
{
    if (_d -> value) {
        _d -> label -> setText(QString("%1").arg(_d -> value -> value()));
    } else {
        logging::warn("SingleValue") << "Value not set!" << logging::endl;
    }
}

}