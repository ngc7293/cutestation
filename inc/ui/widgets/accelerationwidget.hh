#ifndef ACCELERATION_WIDGET_H
#define ACCELERATION_WIDGET_H

#include "ui/widgets/sensorwidget.hh"

#include <QChart>
#include <QDateTimeAxis>
#include <QLabel>
#include <QLineSeries>
#include <QValueAxis>

class AccelerationWidget : public SensorWidget {
    Q_OBJECT

public:
    static const int GRAPH_LENGTH_SEC = 30;

private:
    QtCharts::QChart* chart_;
    QtCharts::QLineSeries *seriesX_, *seriesY_, *seriesZ_, *seriesNorm_;
    QVector<QPointF> valuesX_, valuesY_, valuesZ_, valuesNorm_;
    QtCharts::QDateTimeAxis* axisX;
    QtCharts::QValueAxis* axisY;
    float max_, min_;
    QLabel *peak_, *current_;

public:
    AccelerationWidget();
    virtual ~AccelerationWidget();

    virtual void accept(Message& message);
};

#endif