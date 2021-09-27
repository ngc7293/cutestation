#ifndef CUTE_WIDGETS_VIEWWIDGET_HH_
#define CUTE_WIDGETS_VIEWWIDGET_HH_

#include "widget.hh"

namespace cute::widgets {

class ViewWidget : public Widget {
    Q_OBJECT

private:
    QTimer* timer_;

public:
    ViewWidget(QWidget* parent, const std::string& name);
    virtual ~ViewWidget();

    void start(unsigned refreshRate);

protected slots:
    virtual void refresh() = 0;
};

}

#endif 