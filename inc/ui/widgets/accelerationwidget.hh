#ifndef ACCELERATION_WIDGET_H
#define ACCELERATION_WIDGET_H

#include "ui/widgets/sensorwidget.hh"

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>

using namespace QtCharts;

class AccelerationWidget : public SensorWidget {
    Q_OBJECT

public:
    static const int MAX_DATA_POINTS = 100;

private:
    QChart* chart_;
    QLineSeries *seriesX_, *seriesY_, *seriesZ_, *seriesNorm_;
    QVector<QPointF> valuesX_, valuesY_, valuesZ_, valuesNorm_;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;

public:
    AccelerationWidget();
    virtual ~AccelerationWidget();

    virtual void accept(Message& message);
};

#endif