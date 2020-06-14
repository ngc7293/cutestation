#ifndef WIDGET_H_
#define WIDGET_H_

#include <memory>
#include <string>

#include <QWidget>
#include <QLabel>
#include <QTimer>

#include "data/series.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace cute::widgets {

class Widget : public QWidget {
    Q_OBJECT

protected:
    QLabel* label_;
    std::string name_;
    data::SeriesSP series_;

    QTimer* timer_;

public:
    Widget(QWidget* parent, const std::string& name);
    ~Widget() override;

    virtual bool init(const json& config);

    std::string name() { return name_; }

protected slots:
    virtual void refresh() = 0;
};

} // namespaces

#endif