#ifndef COMMAND_H_
#define COMMAND_H_

#include "proto/packet.h"

namespace cute::data {

class Command : public QObject, public proto::DataEmitter {
    Q_OBJECT
    Q_INTERFACES(cute::proto::DataEmitter)

private:
    proto::DataIngestor* ingestor_;

public:
    Command();
    ~Command();

    proto::DataIngestor* ingestor() const { return ingestor_; }
    void setIngestor(proto::DataIngestor* ingestor);

    template<typename T>
    void setValue(T value);

signals:
    void dataReady(proto::DataSP data);
};

typedef std::shared_ptr<Command> CommandSP;

} // namespaces

#endif