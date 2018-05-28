#ifndef APP_H
#define APP_H

#include <QMainWindow>

#include "workers/serialworker.hh"
#include "ui/widgets/accelerationwidget.hh"

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;
    SerialWorker* serial_;
    AccelerationWidget* accel_widget_;

public:
    explicit App(QWidget* parent = 0);
    ~App();

public slots:
    void onMessage(Message* message);
};

#endif // APP_H