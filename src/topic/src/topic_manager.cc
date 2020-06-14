#include "topic_manager.hh"

#include <shared_mutex>

#include <assert.h>

#include "node.hh"

struct TopicManager::Priv {
    std::shared_ptr<Node> root;
    std::shared_mutex mutex;
};

TopicManager::TopicManager()
    : d_(new Priv)
{
    d_->root = std::make_shared<Node>("");
}

TopicManager::~TopicManager()
{
}

std::shared_ptr<Topic> TopicManager::retrieve(const std::string& name, const std::type_info& type)
{
    std::shared_ptr<Topic> topic;

    {
        std::shared_lock guard(d_->mutex);

        if (topic = find(name)) {
            if (topic->type() == type) {
                return topic;
            }

            return std::shared_ptr<Topic>();
        }
    }

    {
        std::lock_guard guard(d_->mutex);

        if (topic = create(name, type)) {
            return put(topic);
        }
    }

    return std::shared_ptr<Topic>();
}

std::shared_ptr<Topic> TopicManager::find(const std::string& name) const
{
    if (std::shared_ptr<Node> node = NodeFinder::find(d_->root, name)) {
        return node->topic();
    }

    return std::shared_ptr<Topic>();
}

std::shared_ptr<Topic> TopicManager::put(const std::shared_ptr<Topic>& topic)
{
    if (std::shared_ptr<Node> node = NodeFinder::find(d_->root, topic->name(), true)) {
        if (std::shared_ptr<Topic> ntopic = node->topic()) {
            assert(false);
        } else {
            node->setTopic(topic);
            return node->topic();
        }
    }

    return std::shared_ptr<Topic>();
}