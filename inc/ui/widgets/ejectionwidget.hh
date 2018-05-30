#ifndef EJECTION_WIDGET_H
#define EJECTION_WIDGET_H

#include "ui/widgets/sensorwidget.hh"

#include <QDateTime>
#include <QLabel>

class EjectionWidget : public SensorWidget {
    Q_OBJECT

public:
private:
    QLabel *ultrasonic_delay_, *apogee_delay_, *main_altitude_;

public:
    EjectionWidget();
    virtual ~EjectionWidget();

    virtual void accept(Message& message);
};

#endif