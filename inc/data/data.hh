#ifndef DATA_HH_
#define DATA_HH_

#include <QString>

#include "lib/rapidjson/document.h"

class Data {
public:
    enum Type {
        NUMERICAL,
        KEYVALUE,
        GPS,
        VECTOR,
        LOG
    };

private:
    Type type_;
    QString name_;
    qint64 timestamp_;

public:
    static Data* fromJson(rapidjson::Document& json);

public:
    Data(Type type, QString name, qint64 timestamp = -1);
    ~Data();

    Type type() const { return type_; }
    QString name() const { return name_; }
    qint64 timestamp() const { return timestamp_; }
};

#endif // DATA_HH_