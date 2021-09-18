#include "topic/subscriber.hh"

#include <assert.h>

#include "global_topic_manager.hh"

namespace topic {

struct Subscriber::Priv {
    std::vector<std::shared_ptr<Topic>> subscribed;
};

Subscriber::Subscriber()
    : d_(new Priv)
{
}

Subscriber::~Subscriber()
{
    for (std::shared_ptr<Topic> topic : d_->subscribed) {
        topic->unsubscribe(this);
    }
}

bool Subscriber::subscribe_generic(const std::string& name, const std::type_info& type, SubscribeInfo& info)
{
    if (std::shared_ptr<Topic> topic = GlobalTopicManager::get().retrieve(name, type)) {
        if (topic->subscribe(info)) {
            d_->subscribed.push_back(topic);
            return true;
        }
    }
    return false;
}

bool Subscriber::unsubscribe(const std::string& name)
{
    for (auto it = d_->subscribed.begin(); it != d_->subscribed.end(); it++) {
        if ((*it)->name() == name && (*it)->unsubscribe(this)) {
            d_->subscribed.erase(it);
            return true;
        }
    }

    return false;
}

}