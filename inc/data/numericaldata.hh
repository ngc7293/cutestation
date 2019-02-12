#ifndef NUMERICAL_DATA_HH_
#define NUMERICAL_DATA_HH_

#include "data.hh"

class NumericalData : public Data {
private:
    double value_;

public:
    NumericalData(QString name, double value, qint64 timestamp = -1);
    ~NumericalData();

    double value() const { return value_; }
};

#endif // NUMERICAL_DATA_HH_