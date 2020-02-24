#ifndef DATA_TREE_H_
#define DATA_TREE_H_

#include "node.h"

#include "proto/packet.h"

namespace cute { namespace data {

class Tree : public QObject, public PacketIngestor {
    Q_OBJECT
    Q_INTERFACES(PacketIngestor)

private:
    NodeSP root_;

public:
    Tree();
    ~Tree();

    NodeSP root() const { return root_; }

public slots:
    void receivePacket(PacketSP packet) override;
};

}} // namespaces

#endif