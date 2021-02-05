#ifndef TOPIC_LOCAL_TOPIC_MANAGER_HH_
#define TOPIC_LOCAL_TOPIC_MANAGER_HH_

#include "topic_manager.hh"

namespace topic {

class LocalTopicManager : public TopicManager {
protected:
    std::shared_ptr<Topic> create(const std::string& name, const std::type_info& type) const override;
};

}

#endif