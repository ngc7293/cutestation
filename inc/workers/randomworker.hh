#ifndef RANDOMWORKER_H
#define RANDOMWORKER_H

#include <thread>

#include <QObject>

#include "messages/message.hh"

class RandomWorker : public QObject {
    Q_OBJECT
private:
    bool quit_;
    std::thread* internal_;

public:
    RandomWorker();
    virtual ~RandomWorker();

private:
    void run();

public slots:
    void start();
    void stop();

signals:
    void messageReady(Message* message);
};

#endif // SERIALWORKER_H