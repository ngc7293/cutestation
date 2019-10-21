#ifndef TIME_SERIES
#define TIME_SERIES

#include <QLineSeries>

class TimeSeries : public QObject {
    Q_OBJECT

private:
    QtCharts::QLineSeries* series_;

public:
    TimeSeries();
    ~TimeSeries();

    QtCharts::QLineSeries& series() const;
};

#endif