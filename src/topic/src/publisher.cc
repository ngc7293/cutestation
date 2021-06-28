#include "topic/publisher.hh"

#include "local_topic_manager.hh"
#include "global_topic_manager.hh"

namespace topic {

struct Publisher::Priv {
    LocalTopicManager topicmgr;
};

Publisher::Publisher()
    : d_(new Priv)
{
}

Publisher::~Publisher() = default;

bool Publisher::publish_generic(const std::string& name, const topic::time& time, const std::any& value) const
{
    if (std::shared_ptr<Topic> topic = GlobalTopicManager::get().retrieve(name, value.type())) {//d_->topicmgr.retrieve(name, value.type())) {
        topic->publish(time, value);
        return true;
    }

    return false;
}

}