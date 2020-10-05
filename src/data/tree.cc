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

} // namespaces