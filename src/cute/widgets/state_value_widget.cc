#include <QFontDatabase>
#include <QLabel>
#include <QLayout>

#include <log/log.hh>

#include "state_value_widget.hh"

namespace cute::widgets {

struct StateValueWidget::Priv {
    QLabel *label, *value_label;
    std::vector<StateRangeMapping> mapping;
    std::unique_ptr<data::StateValue> value;
};

StateValueWidget::StateValueWidget(QWidget* parent, const std::string& name)
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

StateValueWidget::~StateValueWidget() { }

void StateValueWidget::set_label(const std::string& label)
{
    _d -> label -> setText(QString::fromStdString(label));
}

void StateValueWidget::set_value(std::unique_ptr<data::StateValue>&& value)
{
    _d -> value = std::move(value);
}

void StateValueWidget::set_value_mapping(std::vector<StateRangeMapping>&& mapping)
{
    _d -> mapping = std::move(mapping);
}

void StateValueWidget::refresh()
{
    if (_d -> value) {
        int val = _d -> value -> value();
        std::string display, color, backgroundColor;

        for (const auto& mapping: _d -> mapping) {
            if (mapping.a <= val && val <= mapping.b) {
                display = mapping.display;

                if (QColor(QString::fromStdString(mapping.color)).isValid()) {
                    color = mapping.color;
                } else {
                    color = "black";
                }

                if (QColor(QString::fromStdString(mapping.backgroundColor)).isValid()) {
                    backgroundColor = mapping.backgroundColor;
                } else {
                    backgroundColor = "none";
                }
            }
        }

        _d -> value_label -> setStyleSheet(QString("QLabel { background-color: %1; color: %2; }").arg(backgroundColor.c_str()).arg(color.c_str()));
        _d -> value_label -> setText(display.c_str());

    } else {
        logging::err("NumberValueWidget") << "Value not set!" << logging::endl;
        assert(false);
    }
}

}