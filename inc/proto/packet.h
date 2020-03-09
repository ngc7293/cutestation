#ifndef PROTO_PACKET_H_
#define PROTO_PACKET_H_

#include <memory>

#include <QObject>
#include <QMetaType>

#include "packet.pb.h"

namespace cute::proto {

typedef std::shared_ptr<Data> DataSP;

class DataIngestor {
public slots:
    virtual void receiveData(DataSP data) = 0;
};

class DataEmitter {
public:
    ~DataEmitter() { }
signals:
    virtual void dataReady(DataSP data) = 0;
};

typedef std::shared_ptr<Handshake> HandshakeSP;

class HandshakeIngestor {
public slots:
    virtual void receiveHandshake(HandshakeSP data) = 0;
};

} // namespaces

Q_DECLARE_METATYPE(cute::proto::DataSP)
Q_DECLARE_METATYPE(cute::proto::HandshakeSP);

Q_DECLARE_INTERFACE(cute::proto::DataIngestor, "cute.proto.DataIngestor")
Q_DECLARE_INTERFACE(cute::proto::DataEmitter, "cute.proto.DataEmitter")

#endif