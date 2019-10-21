#ifndef MESSAGE_INGESTOR_H_
#define MESSAGE_INGESTOR_H_

#include <QObject>

#include "proto/packet.pb.h"

class MessageIngestor : public QObject {
public slots:
    virtual void receiveMessage(Packet* msg) = 0;
};

#endif