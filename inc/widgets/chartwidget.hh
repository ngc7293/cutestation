#ifndef CHART_WIDGET_HH_
#define CHART_WIDGET_HH_

#include "widget.hh"

#include <QChart>
#include <QChartView>
#include <QDateTimeAxis>
#include <QLabel>
#include <QLineSeries>
#include <QTimer>
#include <QValueAxis>

class ChartWidget : public Widget {
    Q_OBJECT

private:
    QtCharts::QChart* chart_;
    QtCharts::QChartView* view_;
    Config<ChartWidget>* config_;

    /** For each series you'll need this */
    QString value_;
    QVector<QPointF> values_;
    QtCharts::QLineSeries* series_;

    /* Axis configuration */
    float max_, min_;
    unsigned int graph_length_;
    QtCharts::QDateTimeAxis* axisX;
    QtCharts::QValueAxis* axisY;

    /** Refresh timer **/
    bool always_update_;
    QTimer* timer_;
    qint64 last_refresh_;
    qint64 last_update_;

public:
    ChartWidget();
    virtual ~ChartWidget();

    Config<ChartWidget>* config() { return config_; }

    void setValue(QString value) { value_ = value; }
    void setGraphLength(unsigned int graph_length) { graph_length_ = graph_length; }
    void setAlwaysUpdate(bool always_update) { always_update_ = always_update; }

public slots:
    virtual void accept(Data& data);
    virtual void refresh();
};

#endif // CHART_WIDGET_HH_
