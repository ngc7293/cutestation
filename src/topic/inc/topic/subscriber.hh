#ifndef TOPIC_SUBSCRIBER_HH_
#define TOPIC_SUBSCRIBER_HH_

#include <functional>
#include <memory>
#include <string>

#include "type.hh"
#include "callback.hh"
#include "subscribe_info.hh"

namespace topic {

class Subscriber {
public:
    Subscriber();
    virtual ~Subscriber();

protected:
    template <typename T>
    bool subscribe(const std::string& name, std::function<void(const topic::time&, const T&)> callback)
    {
        SubscribeInfo info;
        info.subscriber = this;
        info.callback = std::dynamic_pointer_cast<GenericCallback>(std::make_shared<Callback<T>>(callback));
        return subscribe_generic(name, typeid(T), info);
    }
    
    bool unsubscribe(const std::string& name);

private:
    bool subscribe_generic(const std::string& name, const std::type_info& type, SubscribeInfo& info);

private:
    struct Priv;
    std::unique_ptr<Priv> d_;
};

}

#endif