#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QChart>
#include <QLineSeries>

class SensorWidget : public QWidget {
    Q_OBJECT

private:
    QLabel* name_;
    QLabel* value_;
    QtCharts::QChart* chart_;
    QtCharts::QLineSeries* series_;
    int count_;

public:
    SensorWidget(QString name);
    virtual ~SensorWidget();

    void setValue(int num, QString val) {
        value_->setText(val);
        series_->append(QPoint(count_++, num));
    }
};

#endif // SENSORWIDGET_H