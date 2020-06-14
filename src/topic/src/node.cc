#include "node.hh"

Node::Node(const std::string& name)
    : _name(name)
{
}

Node::~Node()
{
}

std::shared_ptr<Node> Node::child(const std::string& name) const
{
    if (_children.count(name)) {
        return _children.at(name);
    }

    return std::shared_ptr<Node>();
}

std::shared_ptr<Node> Node::addChild(const std::string& name)
{
    return _children.emplace(name, std::make_shared<Node>(name)).first->second;
}

std::shared_ptr<Node> NodeFinder::find(std::shared_ptr<Node>& root, const std::string& name, bool create)
{
    return NodeFinder(root).find_impl(name, create);
}

NodeFinder::NodeFinder(std::shared_ptr<Node> root)
    : _root(root)
{
}

std::shared_ptr<Node> NodeFinder::find_impl(const std::string& name, bool create)
{
    _create = create;

    for (std::string::size_type i = 0;; i++) {
        _fragments.push_back(name.substr(i, name.find('.', i + 1) - i));

        if ((i = name.find(".", i)) == std::string::npos) {
            break;
        }
    }

    _current = _fragments.begin();
    return visit(_root);
}

std::shared_ptr<Node> NodeFinder::visit(std::shared_ptr<Node>& node)
{
    std::shared_ptr<Node> child;

    if ((child = node->child(*_current))) {
        if (++_current == _fragments.end()) {
            return child;
        }

        return visit(child);
    } else if (_create) {
        child = node->addChild(*_current);

        if (++_current == _fragments.end()) {
            return child;
        }

        return visit(child);
    }

    return std::shared_ptr<Node>();
}