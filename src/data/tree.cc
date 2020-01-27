#include "data/tree.h"

#include <data/time_series.h>

#include "data/node_finder.h"

namespace cute { namespace data {

Tree::Tree()
    : root_(new Node(""))
{
}

Tree::~Tree()
{
}

void Tree::receiveMessage(PacketSP packet)
{
    if (NodeSP node = NodeFinder(packet->source()).visit(root_)) {
        if (SeriesSP series = node->series()) {
            series->accept(packet);
        }
    }
}

}} // namespaces