#ifndef APP_H
#define APP_H

#include <QMainWindow>

#include "ui/widgets/chartwidget.hh"
#include "workers/randomworker.hh"

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;
    RandomWorker* random_;
    ChartWidget* chart_widget1_;
    ChartWidget* chart_widget2_;
    ChartWidget* chart_widget3_;
    ChartWidget* chart_widget4_;

public:
    explicit App(QWidget* parent = 0);
    ~App();

public slots:
    void onMessage(Message* message);
};

#endif // APP_H