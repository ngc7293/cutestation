#include "ui/app.hh"

#include <fstream>
#include <iostream>

#include "ui_app.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);
}

App::~App()
{
    delete ui_;
}