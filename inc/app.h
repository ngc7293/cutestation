#ifndef APP_H_
#define APP_H_

#include <QMainWindow>
#include <QThread>

#include "socket/socket_dispatcher.h"
#include "data/tree.h"

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;
    cute::io::SocketDispatcher* dispatcher_;
    cute::data::Tree* tree_;

public:
    explicit App(QWidget* parent = 0);
    ~App();
};

#endif