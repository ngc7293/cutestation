#ifndef TIME_SERIES
#define TIME_SERIES

#include <QObject>

#include "proto/packet.pb.h"

class Series : public QObject {
    Q_OBJECT

public:
    Series();
    ~Series();

    virtual void accept(const Packet* packet) = 0;
};

#endif