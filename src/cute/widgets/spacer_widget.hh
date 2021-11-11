#ifndef CUTE_WIDGETS_SPACERWIDGET_HH_
#define CUTE_WIDGETS_SPACERWIDGET_HH_

#include "widget.hh"

namespace cute::widgets {

class SpacerWidget: public Widget {
public:
    SpacerWidget(QWidget* parent)
        : Widget(parent, "")
    {
    }

    ~SpacerWidget() override
    {
    }
};

}

#endif