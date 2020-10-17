#ifndef CUTE_WIDGETS_CONTROL_WIDGET_H_
#define CUTE_WIDGETS_CONTROL_WIDGET_H_

#include "widget.h"

#include <topic/publisher.hh>

namespace cute::widgets {

class ControlWidget : public Widget, public topic::Publisher {

public:
    ControlWidget(QWidget* parent, const std::string& name);
    ~ControlWidget() override;
};

}

#endif