#include "data_tree.h"

DataTree::DataTree() { root_ = new DataNode(""); }

DataTree::~DataTree() { delete root_; }

void DataTree::receiveMessage(Packet *packet) {
  root_->accept(packet->source(), 0, packet);
}