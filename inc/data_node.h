#ifndef DATA_NODE_H_
#define DATA_NODE_H_

#include <string>
#include <unordered_map>

#include "proto/packet.pb.h"

class DataNode {
private:
    std::unordered_map<std::string, DataNode*> children_;
    std::string name_;

public:
    DataNode(std::string name);
    ~DataNode();

    void accept(const std::string& source, size_t pos, Packet* packet);

};
#endif