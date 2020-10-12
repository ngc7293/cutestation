#ifndef TOPIC_MOCK_HH_
#define TOPIC_MOCK_HH_

#include "publisher.hh"
#include "subscriber.hh"

namespace topic {

class MockPublisher: public Publisher {
public:
    template <typename T>
    bool callPublish(const std::string& name, const T& value) { return publish(name, value); }
};

class MockSubscriber: public Subscriber {
public:
    template<typename T>
    bool callSubscribe(const std::string& name, std::function<void(const std::chrono::nanoseconds&, const T& value)> method) { return subscribe(name, method); }

    template<typename T>
    bool callUnsubscribe(const std::string& name) { return unsubscribe<T>(name); }
};

}

#endif