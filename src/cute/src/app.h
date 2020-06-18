#ifndef APP_H_
#define APP_H_

#include <QMainWindow>
#include <QThread>

// #include <io/io_dispatcher.h>

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;
    // cute::io::IODispatcher dispatcher;

public:
    explicit App(QWidget* parent = 0);
    ~App();
};

#endif