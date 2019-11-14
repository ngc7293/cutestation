#ifndef SERIAL_HH_
#define SERIAL_HH_

#include <QObject>
#include <QString>

#include "serializer.hh"

#include "shared/interfaces/radio/radio_packet.h"

class Serial : public QObject {
    Q_OBJECT

public:
    static constexpr int SERIAL_BAUDRATE = 460800;

private:
    Serializer* serializer_;

    bool quit_;
    bool connected_;
    int device_;

public:
    Serial(QString device, Serializer* serializer);
    ~Serial();

private:
    bool config();

public slots:
    void work();
    void send(radio_packet_t packet);
    void quit() { quit_ = true; };
};

#endif