#include "data/tree.h"

#include <data/time_series.h>

#include "data/node_finder.h"

#include "log.h"

namespace cute::data {

Tree::Tree()
    : root_(new Node(""))
{
}

Tree::~Tree()
{
}

void Tree::receiveData(proto::DataSP data)
{
    for (const proto::Measurement& measurement : data->measurements()) {
        if (NodeSP node = NodeFinder(measurement.source()).visit(root_)) {
            if (SeriesSP series = node->series()) {
                series->accept(measurement);
            }
        }
    }
}

} // namespaces