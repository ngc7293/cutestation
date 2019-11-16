#ifndef MESSAGE_INGESTOR_H_
#define MESSAGE_INGESTOR_H_

#include <QObject>

#include "proto/packet.h"

class MessageIngestor : public QObject {
public slots:
    virtual void receiveMessage(PacketSP) = 0;
};

#endif