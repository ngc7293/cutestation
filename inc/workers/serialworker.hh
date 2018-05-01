#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <thread>

#include <QObject>

#include "communication/serial.hh"
#include "messages/message.hh"

class SerialWorker : public QObject {
    Q_OBJECT
private:
    Serial* serial_;
    bool quit_;

    std::thread* internal_;

public: 
    SerialWorker();
    SerialWorker(Serial* serial);
    virtual ~SerialWorker();

private:
    void run();

public slots:
    void start();
    void stop();

signals:
    void messageReady(Message* message);
};

#endif // SERIALWORKER_H