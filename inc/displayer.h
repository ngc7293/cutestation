#ifndef DISPLAYER_H_
#define DISPLAYER_H_

#include <cstdint>

#include <vector>
#include <tuple>

#include <QObject>

#include "message_ingestor.h"
#include "proto/packet.h"

class Displayer : public MessageIngestor {
    Q_OBJECT

private:

public:
    Displayer();
    ~Displayer();

public slots:
    void receiveMessage(PacketSP) override;
    void displayMessage(PacketSP);
    void close();
};

#endif