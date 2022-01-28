#include <QFontDatabase>
#include <QLabel>
#include <QLayout>

#include <log/log.hh>
#include <util/json.hh>
#include <cute/data/value_factory.hh>

#include "widget_factory.hh"
#include "value_widget.hh"

namespace cute::widgets {

template<typename Type>
struct ValueWidget<Type>::Priv {
    QLabel *label, *value_label;
    std::vector<RangeMapping<Type>> mapping;
    std::unique_ptr<data::Value<Type>> value;
};

template<typename Type>
ValueWidget<Type>::ValueWidget(QWidget* parent, const std::string& name)
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

template<typename Type>
ValueWidget<Type>::~ValueWidget() = default;

template<typename Type>
void ValueWidget<Type>::set_label(const std::string& label)
{
    _d -> label -> setText(QString::fromStdString(label));
}

template<typename Type>
void ValueWidget<Type>::set_value(std::unique_ptr<data::Value<Type>>&& value)
{
    _d -> value = std::move(value);
}

template<typename Type>
void ValueWidget<Type>::set_value_mapping(std::vector<RangeMapping<Type>>&& mapping)
{
    _d -> mapping = std::move(mapping);
}

template<typename Type>
void ValueWidget<Type>::refresh()
{
    if (_d -> value) {
        Type val = _d -> value -> value();
        std::string display, color, backgroundColor;

        for (const auto& mapping: _d -> mapping) {
            if (mapping.low <= val && val <= mapping.high) {
                display = mapping.displayFormat;

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
        _d -> value_label -> setText(QString::asprintf(display.c_str(), val));

    } else {
        logging::err("NumberValueWidget") << "Value not set!" << logging::endl;
        assert(false);
    }
}

template<typename Type>
ValueWidget<Type>* ValueWidget<Type>::build(const json& config, QWidget* parent)
{
    std::string name, label;
    unsigned refresh_rate;

    if (!(util::json::validate("ValueWidget", config,
        util::json::required(name, "name"),
        util::json::optional(label, "label", "widget"),
        util::json::optional(refresh_rate, "refresh_rate", 2u)
    ))) {
        return nullptr;
    }

    data::Value<Type>* ptr = nullptr;
    if (config.count("source")) {
        ptr = data::ValueFactory::build<Type>(config["source"]);
    }

    std::vector<RangeMapping<Type>> mappings;
    if (config.count("mapping") && config["mapping"].is_object()) {
        mappings = RangeMapping<Type>::buildAll(config["mapping"]);
    } else {
        logging::warn("ValueWidget") << "No mapping configured, displaying raw value";
    }

    if (!ptr) {
        logging::err("ValueWidget") << "Missing or invalid 'source' configuration" << logging::endl;
        return nullptr;
    }

    ValueWidget<Type>* widget = new ValueWidget<Type>(parent, name);
    widget->set_value(std::unique_ptr<data::Value<Type>>(ptr));
    widget->set_value_mapping(std::move(mappings));
    widget->set_label(label);
    widget->start(refresh_rate);
    return widget;
}

}

template class cute::widgets::ValueWidget<int>;
template class cute::widgets::ValueWidget<double>;