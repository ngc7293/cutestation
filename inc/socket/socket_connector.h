#ifndef SOCKET_CONNECTOR_H_
#define SOCKET_CONNECTOR_H_

#include <QObject>
#include <QLocalSocket>
#include <QThread>

#include "proto/packet.h"

namespace cute::data {
    class Source;
}

namespace cute::io {

class SocketConnector : public QObject, public proto::DataEmitter, public proto::DataIngestor {
    Q_OBJECT
    Q_INTERFACES(cute::proto::DataEmitter)
    Q_INTERFACES(cute::proto::DataIngestor)

private:
    QLocalSocket* socket_;

public:
    SocketConnector(QLocalSocket* socket, QThread* thread);
    ~SocketConnector();

private slots:
    void readData();

public slots:
    void close();
    void receiveData(proto::DataSP data) override { };

signals:
    void dataReady(proto::DataSP data) override;
    void connectionClosed();
};

}

#endif