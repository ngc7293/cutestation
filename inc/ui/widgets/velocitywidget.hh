#ifndef VELOCITY_WIDGET_H
#define VELOCITY_WIDGET_H

#include "ui/widgets/sensorwidget.hh"

#include <QChart>
#include <QDateTimeAxis>
#include <QLabel>
#include <QLineSeries>
#include <QValueAxis>

class VelocityWidget : public SensorWidget {
    Q_OBJECT

public:
    static const int GRAPH_LENGTH_SEC = 60;

private:
    QtCharts::QChart* chart_;
    QtCharts::QLineSeries* series_;
    QVector<QPointF> values_;
    float max_, min_;
    QtCharts::QDateTimeAxis* axisX;
    QtCharts::QValueAxis* axisY;
    QLabel *apogee_, *current_;

public:
    VelocityWidget();
    virtual ~VelocityWidget();

    virtual void accept(Message& message);
};

#endif