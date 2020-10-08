#ifndef CUTE_TOPIC_GLOBAL_TOPIC_MANAGER_HH_
#define CUTE_TOPIC_GLOBAL_TOPIC_MANAGER_HH_

#include "topic_manager.hh"

#include <iostream>

class GlobalTopicManager : public TopicManager {
public:
    static GlobalTopicManager& get()
    {
        static GlobalTopicManager instance;
        return instance;
    }

    virtual ~GlobalTopicManager() {}

protected:
    std::shared_ptr<Topic> create(const std::string& name, const std::type_info& type) const override;

private:
    GlobalTopicManager() {}
    GlobalTopicManager(GlobalTopicManager const&) = delete;
    void operator=(GlobalTopicManager const&)     = delete;
};

#endif