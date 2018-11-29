#ifndef DATA_HH_
#define DATA_HH_

#include <QDateTime>

class Data {
private:
    /** Timestamp with milliseconds */
    uint64_t timestamp_;

    /** temp */
    int value_;

public:
    Data(uint64_t timestamp);
    ~Data();

    qint64 timestamp() { return timestamp_; }

    int value() { return value_; }
    void setValue(int value) { value_ = value; }
};

#endif