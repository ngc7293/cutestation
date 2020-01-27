#ifndef DATA_NODE_H_
#define DATA_NODE_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "proto/packet.h"
#include "data/series.h"

namespace cute { namespace data {

class Node;
typedef std::shared_ptr<Node> NodeSP;

class Node {
private:
    std::unordered_map<std::string, NodeSP> children_;
    std::string name_;
    
    SeriesSP series_;

public:
    Node(std::string name);
    ~Node();

    std::string name() const { return name_; };
    NodeSP child(const std::string name) const { return children_.count(name) ? children_.at(name) : NodeSP(); };
    SeriesSP series() const { return series_; }

    NodeSP addChild(std::string name) { return children_.emplace(name, std::make_shared<Node>(name)).first->second; }
};

}} // namespaces

#endif