#ifndef CUTE_WIDGETS_COMPASSWIDGET_HH_
#define CUTE_WIDGETS_COMPASSWIDGET_HH_

#include <utility>

#include <cute/data/dynamic_value.hh>

#include "view_widget.hh"

namespace cute::widgets {

class CompassWidget: public ViewWidget {
    Q_OBJECT

    using ValuePair = std::pair<std::unique_ptr<data::Value>, std::unique_ptr<data::Value>>;

public:
    CompassWidget(QWidget* parent, const std::string& name);
    ~CompassWidget() override;

    void set_radius(double radius);
    void set_reference(ValuePair&& reference);
    void set_target(ValuePair&& target);

protected:
    void paintEvent(QPaintEvent* event) override;

protected slots:
    void refresh() override;

private:
    struct Priv;
    std::unique_ptr<Priv> _d;
};

}

#endif