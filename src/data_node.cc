#include "data_node.h"

#include <chrono>
#include <iostream>

#include "series/time_series.h"

DataNode::DataNode(std::string name)
    : name_(name)
{
    series_ = new TimeSeries();
}

DataNode::~DataNode()
{
    for (auto node : children_) {
        delete node.second;
    }

    delete series_;
}

DataNode* DataNode::find(DataNode& current, const std::string& name, size_t pos)
{
    if (pos >= name.length()) {
        return &current;
    }

    std::string subname = name.substr(pos, name.find('.', pos + 1) - pos);
    DataNode* subnode;

    if ((subnode = current.child(subname)) != nullptr) {
        return find(*subnode, name, pos + name.length() + 1);
    }

    return nullptr;
}