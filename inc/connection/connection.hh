#ifndef CONNECTION_HH_
#define CONNECTION_HH_

#include <QObject>

#include "data/data.hh"

class Connection : public QObject {
    Q_OBJECT

public:
    Connection();
    virtual ~Connection();

public slots:
    void onClose();

signals:
    void closed(Connection* connection);
    void dataReady(Data* data);
};

#endif // CONNECTION_HH_