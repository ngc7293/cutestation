#ifndef SOURCE_HH_
#define SOURCE_HH_

#include <QLocalServer>
#include <QObject>

#include "data/data.hh"

class Source : public QObject {
    Q_OBJECT

private:
    bool quit_;

    QLocalServer server_;

public:
    Source(std::string path);
    virtual ~Source();

public slots:
    void run();
    void read();
    void quit() { quit_ = true; };
signals:
    void dataReady(Data* data);
    void finished();
};

#endif