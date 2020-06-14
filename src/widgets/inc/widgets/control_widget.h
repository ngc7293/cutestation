#ifndef CONTROL_WIDGET_H_
#define CONTROL_WIDGET_H_

#include "widget.h"

#include <topic/publisher.hh>

namespace cute::widgets {

class ControlWidget : public Widget, public Publisher {

public:
    ControlWidget(QWidget* parent, const std::string& name);
    ~ControlWidget() override;

    bool init(const json& config) override;
};

}

#endif