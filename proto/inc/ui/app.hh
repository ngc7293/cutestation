#ifndef APP_HH_
#define APP_HH_

#include <QMainWindow>

namespace Ui {
class App;
}

class App : public QMainWindow {
    Q_OBJECT

private:
    Ui::App* ui_;

public:
    explicit App(QWidget* parent = 0);
    ~App();
};

#endif // APP_HH_