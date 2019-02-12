#ifndef DATA_HH_
#define DATA_HH_

#include <QString>

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
    Data(Type type, QString name, qint64 timestamp = -1);
    ~Data();

    Type type() const { return type_; }
    QString name() const { return name_; }
    qint64 timestamp() const { return timestamp_; }
};

#endif // DATA_HH_