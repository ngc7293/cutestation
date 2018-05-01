#include "ui/app.hh"

#include <sstream>

#include "communication/serialcom.hh"
#include "communication/serialstub.hh"

#include "ui/sensorwidget.hh"

#include "messages/message_defs.h"
#include "messages/rocketstatemessage.hh"

#include "ui_app.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
    , state_widget_(new SensorWidget("State :"))
{
    ui_->setupUi(this);
    serial_ = new SerialWorker(new SerialStub());
    QObject::connect(serial_, SIGNAL(messageReady(Message*)), this, SLOT(onMessage(Message*)));
    serial_->start();
    ui_->chart_vbox->addWidget(state_widget_);
}

App::~App()
{
    delete ui_;
    delete serial_;
}

void App::onMessage(Message* message)
{
    if (message->id() == MSG_ID_ROCKET_STATE) {
        state_widget_->setValue(((RocketStateMessage*)message)->state(), ((RocketStateMessage*)message)->stateString().c_str());
    }
    else if (message->id() == MSG_ID_GYRO) {
        std::stringstream ss;
        ss << message;
        ui_->textEdit->setText(QString(ss.str().c_str()) + "\n" + ui_->textEdit->toPlainText());
    }
    delete message;
}