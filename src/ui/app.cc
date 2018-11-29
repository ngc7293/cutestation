#include "ui/app.hh"
#include "ui_app.h"

#include <iostream>

#include <QThread>

#include "inc/lib/json.hh"

#include "data/data.hh"
#include "source/source.hh"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    connect(ui_->button_test, SIGNAL(clicked()), this, SLOT(onTestButton()));

    QThread* thread = new QThread();
    Source* source = new Source("/home/ngc7293/cute.sock");
    source->moveToThread(thread);
    connect(source, SIGNAL(dataReady(Data*)), this, SLOT(onDataReady(Data*)));
    connect(thread, SIGNAL(started()), source, SLOT(run()));
    connect(source, SIGNAL(finished()), thread, SLOT(quit()));
    connect(source, SIGNAL(finished()), source, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
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

void App::onTestButton()
{
    std::cout << "food, glorious food" << std::endl;
}