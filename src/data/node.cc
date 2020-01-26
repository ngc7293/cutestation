#include "data/node.h"

#include <chrono>
#include <iostream>

#include "series/time_series.h"

namespace cute {
namespace data {

    Node::Node(std::string name)
        : name_(name)
        , series_(new TimeSeries())
    {
    }

    Node::~Node()
    {
    }

}
} // namespaces