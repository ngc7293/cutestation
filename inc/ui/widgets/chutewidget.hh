#ifndef CHUTE_WIDGET_H
#define CHUTE_WIDGET_H

#include "ui/widgets/sensorwidget.hh"

#include <QDateTime>
#include <QLabel>

class ChuteWidget : public SensorWidget {
    Q_OBJECT

public:
    enum ChuteStatus { NONE,
        DETECT,
        FIRED };

private:
    QLabel *main_, *drogue_;

    ChuteStatus main_status_, drogue_status_;
    QDateTime main_fired_timestamp_, drogue_fired_timestamp_;

public:
    ChuteWidget();
    virtual ~ChuteWidget();

    virtual void accept(Message& message);
};

#endif