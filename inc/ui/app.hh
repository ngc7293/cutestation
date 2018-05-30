#ifndef APP_H
#define APP_H

#include <QMainWindow>

#include "ui/widgets/accelerationwidget.hh"
#include "ui/widgets/altitudewidget.hh"
#include "ui/widgets/chutewidget.hh"
#include "ui/widgets/ejectionwidget.hh"
#include "ui/widgets/gpswidget.hh"
#include "ui/widgets/velocitywidget.hh"
#include "workers/serialworker.hh"

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;
    SerialWorker* serial_;
    AccelerationWidget* accel_widget_;
    AltitudeWidget* altitude_widget_;
    VelocityWidget* velocity_widget_;
    ChuteWidget* chute_widget_;
    GPSWidget* gps_widget_;
    EjectionWidget* ejection_widget_;

public:
    explicit App(QWidget* parent = 0);
    ~App();

public slots:
    void onMessage(Message* message);
};

#endif // APP_H