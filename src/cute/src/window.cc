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

QGridLayout* Window::grid()
{
    return ui_->chart_grid;
}

}