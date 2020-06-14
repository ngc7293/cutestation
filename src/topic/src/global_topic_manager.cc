#include "global_topic_manager.hh"

std::shared_ptr<Topic> GlobalTopicManager::create(const std::string& name, const std::type_info& type) const
{
    return std::make_shared<Topic>(name, type);
}