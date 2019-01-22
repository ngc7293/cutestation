#include "ui/app.hh"
#include "ui_app.h"

#include <iostream>

#include <QThread>

#include "lib/json.hh"

#include "connector/unixconnectormanager.hh"
#include "data/data.hh"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    unixconnectormanager_ = new UnixConnectorManager();
}

App::~App()
{
    delete unixconnectormanager_;
    delete ui_;
}