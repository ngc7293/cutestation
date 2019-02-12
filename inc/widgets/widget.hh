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
    class Config;

private:
    QLabel* name_;
    Config* config_;

protected:
    QWidget* container_;
    QHBoxLayout* layout_;

public:
    Widget();
    virtual ~Widget();

    virtual void accept(Data& data) = 0;

    Config* config() { return config_; }
};

#endif // WIDGET_HH_