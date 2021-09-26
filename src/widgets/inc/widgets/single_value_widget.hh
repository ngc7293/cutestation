#ifndef CUTE_WIDGETS_SINGLEVALUEWIDGET_HH_
#define CUTE_WIDGETS_SINGLEVALUEWIDGET_HH_

#include "view_widget.hh"

#include <memory>

#include <data/single_value.hh>

namespace cute::widgets {

class SingleValueWidget : public ViewWidget {
    Q_OBJECT

public:
    SingleValueWidget(QWidget* parent, const std::string& name);
    ~SingleValueWidget() override;

    void set_value(std::unique_ptr<data::SingleValue<double>>&& value);

protected slots:
    void refresh() override;

private:
    struct Priv;
    std::unique_ptr<Priv> _d;
};

}

#endif