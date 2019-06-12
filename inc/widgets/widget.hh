#ifndef WIDGET_HH_
#define WIDGET_HH_

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

#include "data/data.hh"

class Widget : public QWidget {
    Q_OBJECT

protected:
    template <class T>
    class Config;

private:
    QLabel* name_;
    Config<Widget>* config_;

protected:
    QWidget* container_;
    QHBoxLayout* layout_;

public:
    Widget();
    virtual ~Widget();

    virtual void accept(Data& data) = 0;

    Config<Widget>* config() { return config_; }
};

#endif // WIDGET_HH_