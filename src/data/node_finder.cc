#include "data/node_finder.h"

#include <iostream>

#include "data/node.h"

namespace cute::data {

NodeFinder::NodeFinder(std::string name, bool create)
    : create_(create)
{
    for (std::string::size_type i = 0;; i++) {
        fragments_.push_back(name.substr(i, name.find('.', i + 1) - i));

        if ((i = name.find(".", i)) == std::string::npos) {
            break;
        }
    }

    current_ = fragments_.begin();
}

NodeFinder::~NodeFinder()
{
}

NodeSP NodeFinder::visit(NodeSP node)
{
    NodeSP child;

    if ((child = node->child(*current_))) {
        if (++current_ == fragments_.end()) {
            return child;
        }

        return visit(child);
    } else if (create_) {
        child = node->addChild(*current_);

        if (++current_ == fragments_.end()) {
            return child;
        }

        return visit(child);
    }

    return NodeSP();
}

} // namespaces