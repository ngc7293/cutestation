#include "ui/widgets/gpswidget.hh"

#include <QGridLayout>
#include <QVBoxLayout>

#include "messages/gpsdatamessage.hh"
#include "messages/gpsmetamessage.hh"
#include "messages/message_defs.h"

GPSWidget::GPSWidget()
    : SensorWidget("GPS")
{
    status_ = new QLabel("");
    count_ = new QLabel("");
    lat_ = new QLabel("");
    lon_ = new QLabel("");
    alt_ = new QLabel("");

    QVBoxLayout* vbox = new QVBoxLayout();
    QGridLayout* grid = new QGridLayout();
    grid->addWidget(new QLabel("<span style=\"font-weight: bold;\">STATUS</span>"), 0, 0);
    grid->addWidget(status_, 1, 0);
    grid->addWidget(new QLabel("<span style=\"font-weight: bold;\">SATELLITES</span>"), 0, 1);
    grid->addWidget(count_, 1, 1);
    grid->addWidget(new QLabel("<span style=\"font-weight: bold;\">LON</span>"), 2, 0);
    grid->addWidget(lon_, 3, 0);
    grid->addWidget(new QLabel("<span style=\"font-weight: bold;\">LAT</span>"), 2, 1);
    grid->addWidget(lat_, 3, 1);
    grid->addWidget(new QLabel("<span style=\"font-weight: bold;\">ALT</span>"), 2, 2);
    grid->addWidget(alt_, 3, 2);
    vbox->addLayout(grid);
    vbox->addStretch();
    layout_->addLayout(vbox);

    setMinimumHeight(150);
}

GPSWidget::~GPSWidget() {}

void GPSWidget::accept(Message& message)
{
    if (message.id() != MSG_ID_GPS_DATA && message.id() != MSG_ID_GPS_METADATA) {
        return;
    }

    if (message.id() == MSG_ID_GPS_DATA) {
        GPSDataMessage& msg = (GPSDataMessage&)message;
        lon_->setText(QString::number(msg.lon()));
        lat_->setText(QString::number(msg.lat()));
        alt_->setText(QString::number(msg.altitude()));
    }

    if (message.id() == MSG_ID_GPS_METADATA) {
        GPSMetaMessage& msg = (GPSMetaMessage&)message;
        status_->setText(msg.fixString().c_str());
        count_->setText(QString::number(msg.count()));
    }
}