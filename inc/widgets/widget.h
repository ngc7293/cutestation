#ifndef WIDGET_H_
#define WIDGET_H_

#include <string>

#include <QWidget>
#include <QLabel>

#include "series/series.h"

class Widget : public QWidget {
    Q_OBJECT

protected:
    QLabel* label_;
    std::string name_;
    SeriesSP series_;

public:
    Widget(QWidget* parent, std::string name);
    ~Widget() override;

    virtual void init(SeriesSP series);

protected slots:
    virtual void refresh() = 0;
};

#endif