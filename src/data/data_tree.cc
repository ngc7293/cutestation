#include "data/data_tree.h"

#include <series/time_series.h>

DataTree::DataTree()
    : root_(new DataNode(""))
{
}

DataTree::~DataTree()
{
}

DataNodeSP DataTree::find(std::string name)
{
    return DataNode::find(root_, name, 0);
}

void DataTree::receiveMessage(PacketSP packet)
{
    if (DataNodeSP node = find(packet->source())) {
        if (SeriesSP series = node->series()) {
            series->accept(packet);
        }
    }
}