#include "ui/app.hh"

#include <sstream>

#include <termios.h>

#include "communication/serialcom.hh"
#include "communication/serialstub.hh"

#include "ui/widgets/sensorwidget.hh"

#include "messages/message_defs.h"
#include "messages/rocketstatemessage.hh"

#include "ui_app.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);
    serial_ = new SerialWorker(new SerialCom("/dev/ttyUSB0", B115200));
    QObject::connect(serial_, SIGNAL(messageReady(Message*)), this, SLOT(onMessage(Message*)));
    serial_->start();
    accel_widget_ = new AccelerationWidget();
    ui_->chart_vbox->addWidget(accel_widget_);
}

App::~App()
{
    delete ui_;
    delete serial_;
}

void App::onMessage(Message* message)
{
    *accel_widget_ << *message;
    delete message;
}