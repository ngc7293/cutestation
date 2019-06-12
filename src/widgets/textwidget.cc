#include "widgets/textwidget.hh"

#include <iostream>

#include "data/data.hh"
#include "data/keyvaluedata.hh"
#include "data/numericaldata.hh"
#include "widgets/config/widget_config.hh"

TextWidget::TextWidget()
    : Widget()
    , config_(new Widget::Config<TextWidget>(this))
{
    label_ = new QLabel();
    QFont font = label_->font();
    font.setPointSize(24);
    label_->setFont(font);
    label_->setText("alpha");
    layout_->addWidget(label_);
    container_->setMinimumHeight(0);
    container_->setMinimumWidth(100);
}

TextWidget::~TextWidget()
{
}

void TextWidget::accept(Data& data)
{
    if (data.type() == Data::NUMERICAL) {
        if (data.name() == value_) {
            label_->setText(QString::number(((NumericalData&)data).value()));
        }
    }

    if (data.type() == Data::KEYVALUE) {
        int dot = value_.lastIndexOf(':');
        if (data.name() == QStringRef(&value_, 0, dot)) {
            label_->setText(
                ((KeyValueData&)data).value(value_.right(value_.length() - dot - 1)));
        }
    }
}

void TextWidget::setDisplayType(QString type)
{
    if (type.toLower() == "number") {
        display_type_ = NUMERIC;
    } else if (type.toLower() == "string") {
        display_type_ = ENGINEERING;
    } else {
        display_type_ = STRING;
    }
}