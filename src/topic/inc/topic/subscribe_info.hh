#ifndef SUBSCRIBE_INFO_HH_
#define SUBSCRIBE_INFO_HH_

#include <chrono>
#include <memory>

#include <assert.h>

class Subscriber;
class GenericCallback;

struct SubscribeInfo {
    Subscriber* subscriber;
    std::shared_ptr<GenericCallback> callback;
};

#endif