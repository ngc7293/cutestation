#ifndef CUTE_WIDGETS_STATEVALUEWIDGET_HH_
#define CUTE_WIDGETS_STATEVALUEWIDGET_HH_

#include <memory>

#include <nlohmann/json.hpp>

#include <cute/data/value.hh>

#include "view_widget.hh"
#include "range_mapping.hh"

namespace cute::widgets {

template<typename Type>
class ValueWidget : public ViewWidget {
public:
    static ValueWidget<Type>* build(const nlohmann::json& json, QWidget* parent);
public:
    ValueWidget(QWidget* parent, const std::string& name);
    ~ValueWidget() override;

    void set_label(const std::string& label);
    void set_value(std::unique_ptr<data::Value<Type>>&& value);
    void set_value_mapping(std::vector<RangeMapping<Type>>&& mappings);

protected slots:
    void refresh() override;

private:
    struct Priv;
    std::unique_ptr<Priv> _d;
};

}

#endif