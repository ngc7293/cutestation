#include "data/numericaldata.hh"

NumericalData::NumericalData(QString name, double value, qint64 timestamp)
    : Data(NUMERICAL, name, timestamp)
    , value_(value)
{
}

NumericalData::~NumericalData() {}
