#include "ui/app.hh"
#include "ui_app.h"

#include <iostream>

#include <QThread>

#include "lib/json.hh"

#include "data/data.hh"

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

void App::onDataReady(Data* data)
{
    std::cout << "[" << data->timestamp() << "] value=" << data->value() << std::endl;
    delete data;
}