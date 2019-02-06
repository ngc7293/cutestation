#ifndef UNIX_CONNECTOR_MANAGER_HH_
#define UNIX_CONNECTOR_MANAGER_HH_

#include <QLocalServer>

class UnixConnectionManager : public QObject {
    Q_OBJECT

private:
    QLocalServer* server_;

public:
    UnixConnectionManager();
    virtual ~UnixConnectionManager();

private slots:
    void onLocalConnection();

};

#endif // UNIX_CONNECTOR_MANAGER_HH_