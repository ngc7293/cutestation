#ifndef GPS_WIDGET_H
#define GPS_WIDGET_H

#include "ui/widgets/sensorwidget.hh"

#include <QDateTime>
#include <QLabel>

class GPSWidget : public SensorWidget {
    Q_OBJECT

private:
    QLabel *status_, *count_;
    QLabel *lat_, *lon_, *alt_;

public:
    GPSWidget();
    virtual ~GPSWidget();

    virtual void accept(Message& message);
};

#endif