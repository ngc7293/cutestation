#ifndef DATA_NODE_H_
#define DATA_NODE_H_

#include <string>
#include <unordered_map>

#include "proto/packet.h"
#include "series/series.h"

class DataNode {
private:
    std::unordered_map<std::string, DataNode*> children_;
    std::string name_;
    
    Series* series_;

public:
    static DataNode* find(DataNode& start, const std::string& name, size_t pos);

public:
    DataNode(std::string name);
    ~DataNode();

    std::string name() const { return name_; };
    DataNode* child(std::string name) const { return children_.count(name) ? children_.at(name) : nullptr; };
    Series* series() const { return series_; }

    void addChild(std::string name) { children_.emplace(name, new DataNode(name)); }
};

#endif