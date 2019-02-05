#ifndef ALTITUDE_WIDGET_H
#define ALTITUDE_WIDGET_H

#include "ui/widgets/widget.hh"

#include <QChart>
#include <QDateTimeAxis>
#include <QLabel>
#include <QLineSeries>
#include <QValueAxis>
#include <QTimer>

class ChartWidget : public Widget {
    Q_OBJECT

public:
    static const int GRAPH_LENGTH_SEC = 60;

private:
    QtCharts::QChart* chart_;

    QtCharts::QLineSeries* series_;
    QVector<QPointF> values_;

    QTimer* timer_;

    float max_, min_;
    QtCharts::QDateTimeAxis* axisX;
    QtCharts::QValueAxis* axisY;

public:
    ChartWidget();
    virtual ~ChartWidget();

public slots:
    virtual void accept(Message& message);
    virtual void refresh();
};

#endif