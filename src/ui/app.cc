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

    // ui_->chart_grid->addWidget(altitude_widget_, 0, 0, 1, 2);
    // ui_->chart_grid->addWidget(velocity_widget_, 1, 0, 1, 2);
    // ui_->chart_grid->addWidget(accel_widget_,    2, 0, 1, 2);
    // ui_->chart_grid->addWidget(chute_widget_,    3, 0, 1, 1);
    // ui_->chart_grid->addWidget(gps_widget_,      3, 1, 1, 1);
    ui_->chart_grid->addWidget(altitude_widget_, 0, 0, 1, 2);
    ui_->chart_grid->addWidget(velocity_widget_, 1, 1, 1, 1);
    ui_->chart_grid->addWidget(accel_widget_, 2, 1, 1, 1);
    ui_->chart_grid->addWidget(chute_widget_, 1, 0, 1, 1);
    ui_->chart_grid->addWidget(gps_widget_, 2, 0, 1, 1);

    // FIXME: Find a real icon. This only works on my machine
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