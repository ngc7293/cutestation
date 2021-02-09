#ifndef CUTE_WIDGETS_WIDGET_HH_
#define CUTE_WIDGETS_WIDGET_HH_

#include <memory>
#include <string>

#include <QWidget>
#include <QLabel>
#include <QTimer>

#include "data/series.hh"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace cute::widgets {

class Widget : public QWidget {
    Q_OBJECT

protected:
    std::string name_;


public:
    Widget(QWidget* parent, const std::string& name);
    virtual ~Widget();

    std::string name() { return name_; }
    void set_name(const std::string& name) { name_ = name; }
};

} // namespaces

#endif