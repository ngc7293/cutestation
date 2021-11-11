#include <QLabel>
#include <QLayout>

#include <log/log.hh>

#include "single_value_widget.hh"

namespace cute::widgets {

struct SingleValueWidget::Priv {
    QLabel* label;
    std::string format;
    std::unique_ptr<data::Value> value;
};

SingleValueWidget::SingleValueWidget(QWidget* parent, const std::string& name)
    : ViewWidget(parent, name)
    , _d(new Priv)
{
    _d -> label = new QLabel(QString::fromStdString(name), this);
    layout()->addWidget(_d -> label);
}

SingleValueWidget::~SingleValueWidget() { }

void SingleValueWidget::set_format(const std::string& format)
{
    _d -> format = format;
}

void SingleValueWidget::set_value(std::unique_ptr<data::Value>&& value)
{
    _d -> value = std::move(value);
}

void SingleValueWidget::refresh()
{
    if (_d -> value) {
        _d -> label -> setText(QString::asprintf(_d -> format.c_str(), _d -> value -> value()));
    } else {
        logging::err("SingleValue") << "Value not set!" << logging::endl;
        assert(false);
    }
}

}