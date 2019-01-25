#ifndef APP_HH_
#define APP_HH_

#include <QMainWindow>
#include <QThread>

#include "rpc/connection/unixconnectionmanager.hh"
#include "data/data.hh"

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;

    UnixConnectionManager* unixconnectionmanager_;

public:
    explicit App(QWidget* parent = 0);
    ~App();

private slots:
};

#endif /* APP_HH_ */