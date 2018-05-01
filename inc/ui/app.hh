#ifndef APP_H
#define APP_H

#include <QMainWindow>

#include "workers/serialworker.hh"
#include "ui/sensorwidget.hh"

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;
    SerialWorker* serial_;
    SensorWidget* state_widget_;

public:
    explicit App(QWidget* parent = 0);
    ~App();

public slots:
    void onMessage(Message* message);
};

#endif // APP_H