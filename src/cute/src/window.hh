#ifndef CUTE_WINDOW_HH_
#define CUTE_WINDOW_HH_

#include <QMainWindow>

#include <widgets/widget_grid.hh>

namespace Ui {
    class Window;
}

namespace cute::ui {

class Window: public QMainWindow {
private:
    Ui::Window* ui_;
    widgets::WidgetGrid* grid_;

public:
    explicit Window(QObject* parent = nullptr);
    ~Window() override;

    widgets::WidgetGrid* grid();
};

}

#endif