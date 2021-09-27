#include "topic_manager.hh"

#include <shared_mutex>

#include <assert.h>

namespace topic {

struct TopicManager::Priv {
    std::unordered_map<std::string, std::shared_ptr<topic::Topic>> topics;
    std::shared_mutex mutex;
};

TopicManager::TopicManager()
    : d_(new Priv)
{
}

TopicManager::~TopicManager() = default;

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
    auto it = d_->topics.find(name);
    std::shared_ptr<Topic> topic;

    if (it != d_->topics.end()) {
        if (it->second->subscribers() == 0) {
            assert(it->second.use_count() == 1);
            it->second.reset();
            d_->topics.erase(it);
        } else {
            topic = it->second;
        }
    }

    return topic;
}

std::shared_ptr<Topic> TopicManager::put(const std::shared_ptr<Topic>& topic)
{
    std::shared_ptr<Topic> other = find(topic->name());

    if (other) {
        return std::shared_ptr<Topic>();
    } else {
        d_->topics.insert({topic->name(), topic});
        return topic;
    }
}

}