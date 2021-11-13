#include <QFontDatabase>
#include <QLabel>
#include <QLayout>

#include <log/log.hh>

#include "single_value_widget.hh"

namespace cute::widgets {

struct SingleValueWidget::Priv {
    QLabel *label, *value_label;
    std::string format;
    std::unique_ptr<data::Value> value;
};

SingleValueWidget::SingleValueWidget(QWidget* parent, const std::string& name)
    : ViewWidget(parent, name)
    , _d(new Priv)
{
    _d -> label = new QLabel(this);
    QFont labelFont;
    labelFont.setPixelSize(10);
    _d -> label -> setFont(labelFont);
    _d -> label -> setAlignment(Qt::AlignHCenter);

    _d -> value_label = new QLabel(this);
    QFont valueFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    valueFont.setPixelSize(16);
    _d -> value_label -> setFont(valueFont);
    _d -> value_label -> setAlignment(Qt::AlignHCenter);

    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));

    layout()->addWidget(_d -> label);
    layout()->addWidget(_d -> value_label);
}

SingleValueWidget::~SingleValueWidget() { }

void SingleValueWidget::set_label(const std::string& label)
{
    _d -> label -> setText(QString::fromStdString(label));
}

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
        _d -> value_label -> setText(QString::asprintf(_d -> format.c_str(), _d -> value -> value()));
    } else {
        logging::err("SingleValue") << "Value not set!" << logging::endl;
        assert(false);
    }
}

}