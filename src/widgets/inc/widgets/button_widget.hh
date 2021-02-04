#ifndef CUTE_WIDGETS_BUTTON_WIDGET_H_
#define CUTE_WIDGETS_BUTTON_WIDGET_H_

#include "control_widget.hh"

#include <QPushButton>

namespace cute::widgets {

class ButtonWidget : public ControlWidget {

private:
    QPushButton* button_;
    std::string command_;

public:
    ButtonWidget(QWidget* parent, const std::string& name);
    ~ButtonWidget() override;

    void set_command(const std::string& command);

public slots:
    void clicked();
    void refresh() override;
};

}

#endif