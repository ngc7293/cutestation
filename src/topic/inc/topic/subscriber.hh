#ifndef TOPIC_SUBSCRIBER_HH_
#define TOPIC_SUBSCRIBER_HH_

#include <functional>
#include <memory>
#include <string>

#include "callback.hh"
#include "subscribe_info.hh"

namespace topic {

class Subscriber {
public:
    Subscriber();
    virtual ~Subscriber();

protected:
    template <typename T>
    bool subscribe(const std::string& name, std::function<void(const std::chrono::nanoseconds&, const T&)> callback)
    {
        SubscribeInfo info;
        info.subscriber = this;
        info.callback = std::dynamic_pointer_cast<GenericCallback>(std::make_shared<Callback<T>>(callback));
        return subscribe_generic(name, typeid(T), info);
    }
    
    template <typename T>
    bool unsubscribe(const std::string& name)
    {
        return unsubscribe_generic(name, typeid(T));
    }

private:
    bool subscribe_generic(const std::string& name, const std::type_info& type, SubscribeInfo& info);
    bool unsubscribe_generic(const std::string& name, const std::type_info& type);

private:
    struct Priv;
    std::unique_ptr<Priv> d_;
};

}

#endif