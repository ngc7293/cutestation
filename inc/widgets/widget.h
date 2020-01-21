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
    Series* series_;

public:
    Widget(QWidget* parent, std::string name);
    ~Widget();

    void init(Series* series);

protected slots:
    void refresh();
};

#endif