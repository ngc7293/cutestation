#include "data/node.h"

#include <chrono>
#include <iostream>

#include "data/time_series.h"

namespace cute::data {

Node::Node(std::string name)
    : name_(name)
{
}

Node::~Node()
{
}

} // namespaces