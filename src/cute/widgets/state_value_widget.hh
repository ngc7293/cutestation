#ifndef CUTE_WIDGETS_STATEVALUEWIDGET_HH_
#define CUTE_WIDGETS_STATEVALUEWIDGET_HH_

#include <memory>

#include <cute/data/value.hh>

#include "view_widget.hh"

namespace cute::widgets {

struct StateRangeMapping {
    int a, b;
    std::string display;
    std::string color, backgroundColor;
};

class StateValueWidget : public ViewWidget {
    Q_OBJECT

public:
    StateValueWidget(QWidget* parent, const std::string& name);
    ~StateValueWidget() override;

    void set_label(const std::string& label);
    void set_value(std::unique_ptr<data::StateValue>&& value);
    void set_value_mapping(std::vector<StateRangeMapping>&& mapping);

protected slots:
    void refresh() override;

private:
    struct Priv;
    std::unique_ptr<Priv> _d;
};

}

#endif