#ifndef CUTE_WIDGETS_BUTTON_WIDGET_H_
#define CUTE_WIDGETS_BUTTON_WIDGET_H_

#include "control_widget.h"

#include <QPushButton>

namespace cute::widgets {

class ButtonWidget : public ControlWidget {

private:
    QPushButton* button_;
    std::string command_;

public:
    ButtonWidget(QWidget* parent, const std::string& name);
    ~ButtonWidget() override;

public slots:
    void clicked();
    void refresh() override;
};

}

#endif