#ifndef DATA_SOURCE_
#define DATA_SOURCE_

#include <proto/packet.h>

namespace cute::data {

class Source : public QObject, proto::DataIngestor, proto::DataEmitter, proto::HandshakeIngestor, public std::enable_shared_from_this<Source> {
    Q_OBJECT
    Q_INTERFACES(cute::proto::DataIngestor)
    Q_INTERFACES(cute::proto::DataEmitter)
    Q_INTERFACES(cute::proto::HandshakeIngestor)

    struct Priv;

public:
    Source();
    virtual ~Source();

    void close();
    void sendData(proto::DataSP data) { emit dataReady(data); };

public slots:
    void receiveData(proto::DataSP data) override;
    void receiveHandshake(proto::HandshakeSP handshake) override;

signals:
    void dataReady(proto::DataSP data) override;

private:
    Priv& _d;
};

typedef std::shared_ptr<Source> SourceSP;
typedef std::weak_ptr<Source> SourceWP;

}

#endif