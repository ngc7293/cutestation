#include "app.h"

#include <iostream>

#include <QLayout>
#include <QThread>

#include "nlohmann/json.hpp"

#include "../ui/ui_app.h"
#include "configurator.h"
#include "data/tree.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    cute::Configurator configurator;
    configurator.load("config.json");
    configurator.configure(*ui_->gridLayout_2);

    dispatcher_ = new cute::io::SocketDispatcher();

    // FIXME: Find a real icon. This only works on my machine
    setWindowIcon(QIcon("/usr/share/icons/Numix-Circle/48/apps/boostnote.svg"));
}

App::~App()
{
    delete dispatcher_;
    delete ui_;
}
