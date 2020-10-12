#ifndef TOPIC_SUBSCRIBE_INFO_HH_
#define TOPIC_SUBSCRIBE_INFO_HH_

#include <chrono>
#include <memory>

#include <assert.h>

namespace topic {

class Subscriber;
class GenericCallback;

struct SubscribeInfo {
    Subscriber* subscriber;
    std::shared_ptr<GenericCallback> callback;
};

}

#endif