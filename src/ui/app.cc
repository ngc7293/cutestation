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

    altitude_widget_ = new AltitudeWidget();
    velocity_widget_ = new VelocityWidget();
    accel_widget_ = new AccelerationWidget();
    chute_widget_ = new ChuteWidget();
    gps_widget_ = new GPSWidget();

    ui_->chart_vbox->addWidget(altitude_widget_);
    ui_->chart_vbox->addWidget(velocity_widget_);
    ui_->chart_vbox->addWidget(accel_widget_);

    QHBoxLayout* chutegpsbox = new QHBoxLayout();
    chutegpsbox->addWidget(chute_widget_);
    chutegpsbox->addWidget(gps_widget_);
    ui_->chart_vbox->addLayout(chutegpsbox);

    ui_->chart_vbox->addStretch();

    setWindowIcon(QIcon("/usr/share/icons/Numix-Circle/48/apps/boostnote.svg"));
}

App::~App()
{
    delete ui_;
    delete serial_;
}

void App::onMessage(Message* message)
{
    *altitude_widget_ << *message;
    *velocity_widget_ << *message;
    *accel_widget_ << *message;
    *chute_widget_ << *message;
    *gps_widget_ << *message;
    delete message;
}