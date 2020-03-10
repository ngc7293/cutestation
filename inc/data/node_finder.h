#ifndef DATA_NODE_FINDER_H_
#define DATA_NODE_FINDER_H_

#include <memory>
#include <string>
#include <vector>

namespace cute::data { 

class Node;
typedef std::shared_ptr<Node> NodeSP;

class NodeFinder;
typedef std::shared_ptr<NodeFinder> NodeFinderSP;

class NodeFinder {

private:
    std::vector<std::string> fragments_;
    std::vector<std::string>::iterator current_;
    bool create_;

public:
    NodeFinder(std::string name, bool create=false);
    ~NodeFinder();

    NodeSP visit(NodeSP node);
};

} // namespaces

#endif