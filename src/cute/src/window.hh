#ifndef CUTE_WINDOW_HH_
#define CUTE_WINDOW_HH_

#include <QMainWindow>
#include <QGridLayout>

#include <widgets/widget.hh>

namespace Ui {
    class Window;
}

namespace cute::ui {

class Window: public QMainWindow {
private:
    Ui::Window* ui_;

public:
    explicit Window(QObject* parent = nullptr);
    ~Window() override;

    QGridLayout* grid();
};

}

#endif