#include "window.hh"

#include "../ui/ui_window.h"

namespace cute::ui {

Window::Window(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::Window())
{
    ui_->setupUi(this);

    grid_ = new widgets::WidgetGrid(this);
    ui_->chart_hbox->addLayout(grid_);
}

Window::~Window()
{
    delete ui_;
}

widgets::WidgetGrid* Window::grid()
{
    return grid_;
}

}