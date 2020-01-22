#ifndef DATA_NODE_H_
#define DATA_NODE_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "proto/packet.h"
#include "series/series.h"

class DataNode;
typedef std::shared_ptr<DataNode> DataNodeSP;

class DataNode {
private:
    std::unordered_map<std::string, DataNodeSP> children_;
    std::string name_;
    
    SeriesSP series_;

public:
    static DataNodeSP find(DataNodeSP start, const std::string& name, size_t pos);

public:
    DataNode(std::string name);
    ~DataNode();

    std::string name() const { return name_; };
    DataNodeSP child(const std::string name) const { return children_.count(name) ? children_.at(name) : DataNodeSP(); };
    SeriesSP series() const { return series_; }

    void addChild(std::string name) { children_.emplace(name, std::make_shared<DataNode>(name)); }
};


#endif