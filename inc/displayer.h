#ifndef DISPLAYER_H_
#define DISPLAYER_H_

#include <cstdint>

#include <vector>
#include <tuple>

#include <QObject>

#include "proto/packet.pb.h"
#include "message_ingestor.h"

class Displayer : public MessageIngestor {
    Q_OBJECT

private:

public:
    Displayer();
    ~Displayer();

public slots:
    void receiveMessage(Packet* msg) override;
    void displayMessage(Packet* msg);
    void close();
};

#endif