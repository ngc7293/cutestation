#ifndef WIDGET_HH_
#define WIDGET_HH_

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

#include "messages/message.hh"

class Widget : public QWidget {
    Q_OBJECT

protected:
    class Config;

private:
    QString name_;

protected:
    QWidget* container_;
    QHBoxLayout* layout_;

public:
    Widget(QString name);
    virtual ~Widget();

    virtual void accept(Message& message) = 0;
    friend Widget& operator<<(Widget& widget, Message& message);

    virtual void setMinimumHeight(int minh);
};

#endif // WIDGET_HH_