#include "ui/widgets/chutewidget.hh"


#include <QVBoxLayout>

#include "messages/parachutestatemessage.hh"
#include "messages/message_defs.h"

ChuteWidget::ChuteWidget()
    : SensorWidget("Parachute")
{
    main_ = new QLabel("");
    drogue_ = new QLabel("");

    main_status_ = NONE;
    drogue_status_ = NONE;

    main_fired_timestamp_ = QDateTime::currentDateTime();
    drogue_fired_timestamp_ = QDateTime::currentDateTime();

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(new QLabel("<span style=\"font-weight: bold;\">DROGUE</span>"));
    vbox->addWidget(drogue_);
    vbox->addWidget(new QLabel("<span style=\"font-weight: bold;\">MAIN</span>"));
    vbox->addWidget(main_);
    vbox->addStretch();
    layout_->addLayout(vbox);

    setMinimumHeight(150);
}

ChuteWidget::~ChuteWidget() { }

void ChuteWidget::accept(Message& message)
{
    if (message.id() != MSG_ID_PARACHUTE_STATE) {
        return;
    }

    ParachuteStateMessage& msg = (ParachuteStateMessage&)message;


    if (msg.main_fired()) {
        if (main_status_ != FIRED) {
            main_fired_timestamp_ = QDateTime::currentDateTime();
        }
        main_status_ = FIRED;
    }
    else if (msg.main_detect()) {
        main_status_ = DETECT;
    }
    else {
        main_status_ = NONE;
    }

    switch (main_status_) {
        case NONE:
            main_->setText("<span style=\"color: darkgreen\">Disarmed</span>"); break;
        case DETECT:
            main_->setText("<span style=\"color: red\">Armed</span>"); break;
        case FIRED:
            main_->setText(QString("Fired at %1").arg(main_fired_timestamp_.toString("HH:mm:ss")));
    }

    if (msg.drogue_fired()) {
        if (drogue_status_ != FIRED) {
            drogue_fired_timestamp_ = QDateTime::currentDateTime();
        }
        drogue_status_ = FIRED;
    }
    else if (msg.drogue_detect()) {
        drogue_status_ = DETECT;
    }
    else {
        drogue_status_ = NONE;
    }

    switch (drogue_status_) {
        case NONE:
            drogue_->setText("<span style=\"color: darkgreen\">Disarmed</span>"); break;
        case DETECT:
            drogue_->setText("<span style=\"color: red\">Armed</span>"); break;
        case FIRED:
            drogue_->setText(QString("Fired at %1").arg(main_fired_timestamp_.toString("HH:mm:ss")));
    }
}