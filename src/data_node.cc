#include "data_node.h"

#include <chrono>
#include <iostream>

DataNode::DataNode(std::string name) : name_(name) {}

DataNode::~DataNode() {
  for (auto node : children_) {
    delete node.second;
  }
}

void DataNode::accept(const std::string &source, size_t pos, PacketSP packet) {
  if (pos >= source.length()) {
    // series_->accept(packet);
    return;
  }

  std::string name = source.substr(pos, source.find('.', pos + 1) - pos);
  auto it = children_.find(name);

  if (it == children_.end()) {
    auto baby = children_.emplace(name, new DataNode(name));

    if (baby.second) {
      it = baby.first;
    }
  }

  it->second->accept(source, pos + name.length() + 1, packet);
}