#ifndef DATA_TREE_H_
#define DATA_TREE_H_

#include "node.h"

#include "proto/packet.h"

namespace cute::data {

class Tree {
private:
    NodeSP root_;

private:
    Tree();

public:
    Tree(Tree const&) = delete;
    void operator=(Tree const&) = delete;
    ~Tree();

    static NodeSP root() { 
        static Tree instance_;
        return instance_.root_; 
    }
};

} // namespaces

#endif