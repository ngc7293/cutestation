#ifndef APP_HH_
#define APP_HH_

#include <QMainWindow>
#include <QThread>

#include "data/data.hh"
#include "source/source.hh"

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

private slots:
    void onDataReady(Data* data);
    void onTestButton();
};

#endif /* APP_HH_ */