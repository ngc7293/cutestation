#ifndef DATA_SOURCE_
#define DATA_SOURCE_

#include "packet.pb.h"

#include <memory>

#include <topic/publisher.hh>

#include <QObject>

namespace cute::data {

class Source : public QObject, public std::enable_shared_from_this<Source>, public Publisher {
    Q_OBJECT

    struct Priv;

public:
    Source();
    virtual ~Source();

    void close();
    void sendData(std::shared_ptr<proto::Data> data) { emit dataReady(data); };

public slots:
    void receiveData(std::shared_ptr<proto::Data> data);
    void receiveHandshake(std::shared_ptr<proto::Handshake> handshake);

signals:
    void dataReady(std::shared_ptr<proto::Data> data);

private:
    Priv& _d;
};

typedef std::shared_ptr<Source> SourceSP;
typedef std::weak_ptr<Source> SourceWP;

}

#endif