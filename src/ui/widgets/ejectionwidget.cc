#include "ui/widgets/ejectionwidget.hh"

#include <QVBoxLayout>

#include "messages/ejectionsettingsmessage.hh"
#include "messages/message_defs.h"

EjectionWidget::EjectionWidget()
    : SensorWidget("Ejection settings")
{
    main_altitude_ = new QLabel("");
    ultrasonic_delay_ = new QLabel("");
    apogee_delay_ = new QLabel("");

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(new QLabel("<span style=\"font-weight: bold;\">ULTRASONIC DELAY</span>"));
    vbox->addWidget(ultrasonic_delay_);
    vbox->addWidget(new QLabel("<span style=\"font-weight: bold;\">APOGEE DELAY</span>"));
    vbox->addWidget(apogee_delay_);
    vbox->addWidget(new QLabel("<span style=\"font-weight: bold;\">MAIN ALTITUDE</span>"));
    vbox->addWidget(main_altitude_);
    vbox->addStretch();
    layout_->addLayout(vbox);

    //    setMinimumHeight(120);
}

EjectionWidget::~EjectionWidget() {}

void EjectionWidget::accept(Message& message)
{
    if (message.id() != MSG_ID_EJECTION_SETTINGS) {
        return;
    }

    EjectionSettingsMessage& msg = (EjectionSettingsMessage&)message;
    ultrasonic_delay_->setText(QString("%1ms").arg(msg.ultrasonic_delay()));
    apogee_delay_->setText(QString("%1ms").arg(msg.ejection_delay()));
    main_altitude_->setText(QString("%1m").arg(msg.ejection_altitude()));
}