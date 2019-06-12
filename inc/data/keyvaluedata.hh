#ifndef KEYVALUE_DATA_HH_
#define KEYVALUE_DATA_HH_

#include "data.hh"

#include <QMap>

class KeyValueData : public Data {
private:
    QMap<QString, QString> store_;

public:
    KeyValueData(QString name, qint64 timestamp = -1);
    ~KeyValueData();

    void add(QString key, QString value);

    QString value(QString key);
};

#endif // KEYVALUE_DATA_HH_