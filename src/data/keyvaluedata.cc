#include "data/keyvaluedata.hh"

KeyValueData::KeyValueData(QString name, qint64 timestamp)
    : Data(KEYVALUE, name, timestamp)
{
}

KeyValueData::~KeyValueData() {}

void KeyValueData::add(QString key, QString value)
{
    store_.insert(key, value);
}

QString KeyValueData::value(QString key)
{
    return store_.value(key);
}