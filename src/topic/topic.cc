#include "topic.hh"

#include <algorithm>
#include <shared_mutex>
#include <typeindex>

#include "topic/callback.hh"

namespace topic {

struct Topic::Priv {
    std::string name;
    const std::type_info& type;

    std::vector<SubscribeInfo> subscribers;
    std::shared_mutex mutex;

    // Exceptionnally this Priv class needs a constructor since std::type_info
    // cannot be stored by value (hence no default constructor)
    Priv(const std::type_info& type)
        : type(type)
    {
    }
};

Topic::Topic(const std::string& name, const std::type_info& type)
    : d_(new Priv(type))
{
    d_->name = name;
}

Topic::~Topic() = default;

std::string Topic::name() const
{
    return d_->name;
}

const std::type_info& Topic::type() const
{
    return d_->type;
}

std::size_t Topic::subscribers() const
{
    return d_->subscribers.size();
}

bool Topic::subscribe(const SubscribeInfo& incoming)
{
    std::lock_guard guard(d_->mutex);

    for (SubscribeInfo& existing: d_->subscribers) {
        if (existing.subscriber == incoming.subscriber) {
            return false;
        }
    }

    d_->subscribers.push_back(incoming);
    return true;
}

bool Topic::unsubscribe(Subscriber* subscriber)
{
    std::lock_guard guard(d_->mutex);

    auto it = std::find_if(d_->subscribers.begin(), d_->subscribers.end(), [&subscriber](const SubscribeInfo& info) {
        return (info.subscriber == subscriber);
    });

    if (it != d_->subscribers.end()) {
        d_->subscribers.erase(it);
        return true;
    }

    return false;
}

void Topic::publish(const topic::time& time, const std::any& value)
{
    std::shared_lock lock(d_->mutex);

    for (const SubscribeInfo& subscriber: d_->subscribers) {
        if (subscriber.callback) {
            subscriber.callback->operator()(time, value);
        }
    }
}

}