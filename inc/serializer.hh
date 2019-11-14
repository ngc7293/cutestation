#ifndef SERIALIZER_HH_
#define SERIALIZER_HH_

#include <QObject>

#include "shared/interfaces/radio/radio_packet.h"

class Serializer : public QObject {
    Q_OBJECT

public:
    Serializer();
    ~Serializer();

public slots:
    void serialize(radio_packet_t packet);
};

#endif