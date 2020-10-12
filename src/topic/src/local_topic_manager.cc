#include "local_topic_manager.hh"

#include "global_topic_manager.hh"

namespace topic {

std::shared_ptr<Topic> LocalTopicManager::create(const std::string& name, const std::type_info& type) const
{
    return GlobalTopicManager::get().retrieve(name, type);
}

}