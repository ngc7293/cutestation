#ifndef CONNECTION_HH_
#define CONNECTION_HH_

#include <QObject>

#include <shared/interfaces/radio/radio_packet.h>

#include "data/data.hh"

class Connection : public QObject {
    Q_OBJECT

public:
    Connection();
    virtual ~Connection();

public slots:
    virtual void writeData(radio_packet_t packet) = 0;
    void onClose();

signals:
    void closed(Connection* connection);
    void dataReady(Data* data);
};

#endif // CONNECTION_HH_