#ifndef UNIX_CONNECTOR_MANAGER_HH
#define UNIX_CONNECTOR_MANAGER_HH

#include <QLocalServer>

class UnixConnectorManager : public QObject {
    Q_OBJECT

private:
    QLocalServer* server_;

public:
    UnixConnectorManager();
    virtual ~UnixConnectorManager();

private slots:
    void onNewConnection();

};

#endif