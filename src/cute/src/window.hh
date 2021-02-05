#ifndef CUTE_WINDOW_HH_
#define CUTE_WINDOW_HH_

#include <QMainWindow>

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

    void addWidget(widgets::Widget* widget, unsigned x, unsigned y, unsigned rowspan = 1, unsigned colspan = 1);
};

}

#endif