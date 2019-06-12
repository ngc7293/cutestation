#ifndef TEXT_WIDGET_HH_
#define TEXT_WIDGET_HH_

#include "widget.hh"

#include <QLabel>

class TextWidget : public Widget {
    Q_OBJECT

public:
    enum DisplayType {
        STRING,
        NUMERIC,
        ENGINEERING
    };

private:
    Config<TextWidget>* config_;

    DisplayType display_type_;
    QString value_;

    QLabel* label_;

public:
    TextWidget();
    virtual ~TextWidget();

    Config<TextWidget>* config() { return config_; }

    void setValue(QString value) { value_ = value; }

    void setDisplayType(QString type);
    void setDisplayType(DisplayType type) { display_type_ = type; }

public slots:
    virtual void accept(Data& data);
};

#endif // CHART_WIDGET_HH_
