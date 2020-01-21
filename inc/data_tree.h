#ifndef DATA_TREE_H_
#define DATA_TREE_H_

#include "data_node.h"
#include "message_ingestor.h"

#include "proto/packet.h"

class DataTree : public MessageIngestor {
    Q_OBJECT

private:
    DataNode* root_;

public:
    DataTree();
    ~DataTree();

    DataNode& root() const { return *root_; }
    DataNode* find(std::string name) { return DataNode::find(*root_, name, 0); }

public slots:
    void receiveMessage(PacketSP packet) override;
};

#endif