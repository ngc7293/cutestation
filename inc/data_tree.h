#ifndef DATA_TREE_H_
#define DATA_TREE_H_

#include "data_node.h"
#include "message_ingestor.h"
#include "proto/packet.pb.h"

class DataTree : public MessageIngestor {
    Q_OBJECT

private:
    DataNode* root_;

public:
    DataTree();
    ~DataTree();

public slots:
    void receiveMessage(Packet* packet) override;
};

#endif