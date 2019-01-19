#include "ui/app.hh"
#include "ui_app.h"

#include <iostream>

#include <QThread>

#include "lib/json.hh"

#include "data/data.hh"
#include "connector/unixconnectormanager.hh"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    new UnixConnectorManager();
}

App::~App()
{
    delete ui_;
}