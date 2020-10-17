#include "window.hh"

#include "../ui/ui_window.h"

namespace cute::ui {

Window::Window(QObject* parent)
    : ui_(new Ui::Window())
{
    ui_->setupUi(this); 
}

Window::~Window()
{
    delete ui_;
}

void Window::addWidget(widgets::Widget* widget, unsigned x, unsigned y, unsigned rowspan, unsigned colspan)
{
    if (widget) {
        ui_->chart_grid->addWidget((QWidget*)widget, x, y, rowspan, colspan);
    }
}

}