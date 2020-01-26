#ifndef DATA_TREE_H_
#define DATA_TREE_H_

#include "node.h"
#include "message_ingestor.h"

#include "proto/packet.h"

namespace cute { namespace data {

class Tree : public MessageIngestor {
    Q_OBJECT

private:
    NodeSP root_;

public:
    Tree();
    ~Tree();

    NodeSP root() const { return root_; }

public slots:
    void receiveMessage(PacketSP packet) override;
};

}} // namespaces

#endif