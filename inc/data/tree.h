#ifndef DATA_TREE_H_
#define DATA_TREE_H_

#include "node.h"

#include "proto/packet.h"

namespace cute::data {

class Tree : public QObject, public proto::DataIngestor {
    Q_OBJECT
    Q_INTERFACES(cute::proto::DataIngestor)

private:
    NodeSP root_;

public:
    Tree();
    ~Tree();

    NodeSP root() const { return root_; }

public slots:
    void receiveData(proto::DataSP data) override;
};

} // namespaces

#endif