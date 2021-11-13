#ifndef CUTE_WIDGETS_WIDGET_HH_
#define CUTE_WIDGETS_WIDGET_HH_

#include <memory>
#include <string>

#include <QWidget>
#include <QLabel>
#include <QTimer>

#include "nlohmann/json.hpp"

#include <cute/data/series.hh>

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

#if (not NDEBUG)
    void paintEvent(QPaintEvent *event) override;
#endif
};

} // namespaces

#endif