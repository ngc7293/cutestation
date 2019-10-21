#include "timeseries.h"

TimeSeries::TimeSeries()
    : series_(new QtCharts::QLineSeries())
{
}

TimeSeries::~TimeSeries()
{
    delete series_;
}