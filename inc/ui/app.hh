#ifndef APP_HH_
#define APP_HH_

#include <QMainWindow>

#include "widgets/chartwidget.hh"
#include "connection/unixconnectionmanager.hh"

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;
    ChartWidget* chart_widget1_;
    ChartWidget* chart_widget2_;
    ChartWidget* chart_widget3_;
    ChartWidget* chart_widget4_;

    UnixConnectionManager* unixconnectionmanager_;

public:
    explicit App(QWidget* parent = 0);
    ~App();

public slots:
    void onMessage(Message* message);
};

#endif // APP_HH_