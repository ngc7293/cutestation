#ifndef SOCKET_CONNECTOR_H_
#define SOCKET_CONNECTOR_H_

#include <QObject>
#include <QLocalSocket>
#include <QThread>

#include <packet.pb.h>

#include <data/source.h>

namespace cute::data {
    class Source;
}

namespace cute::io {

class SocketConnector : public QObject {
    Q_OBJECT

private:
    QLocalSocket* socket_;
    data::SourceSP source_;

public:
    SocketConnector(QLocalSocket* socket, QThread* thread);
    ~SocketConnector();

private slots:
    void readData();

public slots:
    void close();

signals:
    void connectionClosed();
};

}

#endif