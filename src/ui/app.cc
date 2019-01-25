#include "ui/app.hh"
#include "ui_app.h"

#include <iostream>

#include <QThread>

#include "rpc/connection/connectionmanager.hh"
#include "data/data.hh"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);
}

App::~App()
{
    ConnectionManager::get().closeAll();
    delete ui_;
}