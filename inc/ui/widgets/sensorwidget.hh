#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>

#include "messages/message.hh"

class SensorWidget : public QWidget {
    Q_OBJECT

private:
    QString name_;

protected:
    QHBoxLayout* layout_;

public:
    SensorWidget(QString name);
    virtual ~SensorWidget();

    virtual void accept(Message& message) = 0;
    friend SensorWidget& operator<<(SensorWidget& widget, Message& message);

private slots:
    void onChecked(bool checked);
};

#endif // SENSORWIDGET_H