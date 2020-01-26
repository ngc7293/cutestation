#ifndef WIDGET_H_
#define WIDGET_H_

#include <string>

#include <QWidget>
#include <QLabel>
#include <QTimer>

#include "series/series.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Widget : public QWidget {
    Q_OBJECT

protected:
    QLabel* label_;
    std::string name_;
    SeriesSP series_;

    QTimer* timer_;

public:
    Widget(QWidget* parent, std::string name);
    ~Widget() override;

    virtual bool init(SeriesSP series, const json& config = json());

protected slots:
    virtual void refresh() = 0;
};

#endif