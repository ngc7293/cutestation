#ifndef TOPIC_TOPIC_HH_
#define TOPIC_TOPIC_HH_

#include <any>
#include <chrono>
#include <functional>
#include <memory>
#include <vector>

#include "topic/type.hh"
#include "topic/subscribe_info.hh"

namespace topic {

class Topic {
public:
    Topic(const std::string& name, const std::type_info& type);
    virtual ~Topic();

    std::string name() const;
    const std::type_info& type() const;

    bool subscribe(const SubscribeInfo& subscribeinfo);
    bool unsubscribe(Subscriber* subscriber);

    void publish(const topic::time& time, const std::any& value);

private:
    struct Priv;
    std::unique_ptr<Priv> d_;
};

}

#endif