#ifndef NODE_HH_
#define NODE_HH_

#include "topic.hh"

#include <memory>
#include <vector>
#include <unordered_map>

class Node {
public:
    Node(const std::string& name);
    ~Node();

    std::string name() const { return _name; };
    std::shared_ptr<Topic> topic() const { return _topic; };

    void setTopic(std::shared_ptr<Topic> topic) { _topic = topic; }

    std::shared_ptr<Node> child(const std::string& name) const;
    std::shared_ptr<Node> addChild(const std::string& name);

private:
    std::string _name;
    std::shared_ptr<Topic> _topic;
    std::unordered_map<std::string, std::shared_ptr<Node>> _children;
};

class NodeFinder {
public:
    static std::shared_ptr<Node> find(std::shared_ptr<Node>& root, const std::string& name, bool create = false);

private:
    NodeFinder(std::shared_ptr<Node> root);
    std::shared_ptr<Node> find_impl(const std::string& name, bool create);
    std::shared_ptr<Node> visit(std::shared_ptr<Node>& node);

private:
    std::shared_ptr<Node> _root;
    std::vector<std::string> _fragments;
    std::vector<std::string>::const_iterator _current;
    bool _create;
};

#endif