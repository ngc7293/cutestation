#ifndef APP_H_
#define APP_H_

#include <QMainWindow>
#include <QThread>

#include "socket_dispatcher.h"

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;
    std::shared_ptr<cute::io::SocketDispatcher> socket_;

public:
    explicit App(QWidget* parent = 0);
    ~App();
};

#endif