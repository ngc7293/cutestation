#ifndef SOCKET_CONNECTOR_H_
#define SOCKET_CONNECTOR_H_

#include <QObject>
#include <QLocalSocket>
#include <QThread>

#include "proto/packet.h"

#include "data/source.h"

namespace cute::data {
    class Source;
}

namespace cute::io {

class SocketConnector : public QObject, proto::DataEmitter, proto::DataIngestor, proto::HandshakeEmitter {
    Q_OBJECT
    Q_INTERFACES(cute::proto::DataEmitter)
    Q_INTERFACES(cute::proto::DataIngestor)
    Q_INTERFACES(cute::proto::HandshakeEmitter)

private:
    QLocalSocket* socket_;
    data::Source* source_;

public:
    SocketConnector(QLocalSocket* socket, QThread* thread);
    ~SocketConnector();

private slots:
    void readData();

public slots:
    void close();
    void receiveData(proto::DataSP data) override;

signals:
    void dataReady(proto::DataSP data) override;
    void handshakeReady(proto::HandshakeSP handshake) override;

    void connectionClosed();
};

}

#endif