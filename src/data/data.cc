#include "data/data.hh"

#include <QDateTime>

Data::Data(Type type, QString name, qint64 timestamp)
    : type_(type)
    , name_(name)
{
    if (timestamp == -1) {
        timestamp_ = QDateTime::currentDateTime().toMSecsSinceEpoch();
    } else {
        timestamp_ = timestamp;
    }
}

Data::~Data() {}
