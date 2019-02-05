#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

#include "messages/message.hh"

class Widget : public QWidget {
    Q_OBJECT

private:
    QString name_;

protected:
    QWidget* container_;
    QHBoxLayout* layout_;
    QGroupBox* group_;

public:
    Widget(QString name);
    virtual ~Widget();

    virtual void accept(Message& message) = 0;
    friend Widget& operator<<(Widget& widget, Message& message);

    virtual void setMinimumHeight(int minh);

private slots:
    void onChecked(bool checked);
};

#endif // SENSORWIDGET_H