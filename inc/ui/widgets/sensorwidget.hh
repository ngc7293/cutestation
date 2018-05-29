#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

#include "messages/message.hh"

class SensorWidget : public QWidget {
    Q_OBJECT

private:
    QString name_;

protected:
    QWidget* container_;
    QHBoxLayout* layout_;
    QGroupBox* group_;

public:
    SensorWidget(QString name);
    virtual ~SensorWidget();

    virtual void accept(Message& message) = 0;
    friend SensorWidget& operator<<(SensorWidget& widget, Message& message);

    virtual void setMinimumHeight(int minh);

private slots:
    void onChecked(bool checked);
};

#endif // SENSORWIDGET_H