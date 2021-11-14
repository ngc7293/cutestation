#ifndef CUTE_WIDGETS_NumberValueWidget_HH_
#define CUTE_WIDGETS_NumberValueWidget_HH_

#include <memory>

#include <cute/data/value.hh>

#include "view_widget.hh"

namespace cute::widgets {

class NumberValueWidget : public ViewWidget {
    Q_OBJECT

public:
    NumberValueWidget(QWidget* parent, const std::string& name);
    ~NumberValueWidget() override;

    void set_label(const std::string& label);
    void set_format(const std::string& format);
    void set_value(std::unique_ptr<data::NumberValue>&& value);

protected slots:
    void refresh() override;

private:
    struct Priv;
    std::unique_ptr<Priv> _d;
};

}

#endif