#ifndef LOCAL_TOPIC_MANAGER_HH_
#define LOCAL_TOPIC_MANAGER_HH_

#include "topic_manager.hh"

class LocalTopicManager : public TopicManager {
protected:
    std::shared_ptr<Topic> create(const std::string& name, const std::type_info& type) const override;
};

#endif