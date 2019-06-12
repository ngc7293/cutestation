#include "data/data.hh"
#include "data/keyvaluedata.hh"
#include "data/numericaldata.hh"

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

Data* Data::fromJson(rapidjson::Document& json)
{
    QString type = json["type"].GetString();

    if (type == "numeric") {
        return new NumericalData(json["name"].GetString(), json["value"].GetDouble());
    }
    if (type == "keyvalue") {
        KeyValueData* data = new KeyValueData(json["name"].GetString());
        for (rapidjson::Value::ConstMemberIterator itr = json.MemberBegin(); itr != json.MemberEnd(); ++itr) {
            if (strcmp(itr->name.GetString(), "name") != 0 && strcmp(itr->name.GetString(), "type") != 0) {
                if (itr->value.IsString()) {
                    data->add(itr->name.GetString(), itr->value.GetString());
                } else if (itr->value.IsNumber()) {
                    data->add(itr->name.GetString(), QString::number(itr->value.GetDouble()));
                }
            }
        }
        return data;
    }
    return nullptr;
}