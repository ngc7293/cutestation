#ifndef WIDGET_HH_
#define WIDGET_HH_

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLabel>

#include "messages/message.hh"

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

    virtual void accept(Message& message) = 0;

    Config* config() { return config_; }
};

#endif // WIDGET_HH_