#ifndef TIME_SERIES
#define TIME_SERIES

#include <QObject>

#include "proto/packet.h"

class Series : public QObject {
    Q_OBJECT

public:
    Series();
    ~Series();

    virtual void accept(const PacketSP) = 0;
};

#endif