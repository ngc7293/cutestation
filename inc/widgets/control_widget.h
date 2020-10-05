#ifndef CONTROL_WIDGET_H_
#define CONTROL_WIDGET_H_

#include "widget.h"

#include "data/command.h"

namespace cute::widgets {

class ControlWidget : public Widget {

protected:
    data::SeriesSP series_;
    data::CommandSP command_;

public:
    ControlWidget(QWidget* parent, std::string name);
    ~ControlWidget() override;

    bool init(data::SeriesSP series, const json& config) override;
    virtual bool init(data::SeriesSP series, data::CommandSP command, const json& config);
};

}

#endif