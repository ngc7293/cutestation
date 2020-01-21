#include "data_tree.h"

DataTree::DataTree()
{
    root_ = new DataNode("");
}

DataTree::~DataTree()
{
    delete root_;
}

void DataTree::receiveMessage(PacketSP packet)
{
    DataNode* node;
    if ((node = DataNode::find(*root_, packet->source(), 0)) != nullptr) {
        node->series()->accept(packet);
    }
}