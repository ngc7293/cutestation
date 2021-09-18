#ifndef TOPIC_MOCK_HH_
#define TOPIC_MOCK_HH_

#include "publisher.hh"
#include "subscriber.hh"
#include "type.hh"

namespace topic {

class MockPublisher: public Publisher {
public:
    template <typename T>
    bool callPublish(const std::string& name, const T& value) { return publish(name, value); }

    template <typename T>
    bool callPublish(const std::string& name, const T& value, const topic::time& when) { return publish(name, value, when); }
};

class MockSubscriber: public Subscriber {
public:
    template<typename T>
    bool callSubscribe(const std::string& name, std::function<void(const topic::time&, const T& value)> method) { return subscribe(name, method); }

    bool callUnsubscribe(const std::string& name) { return unsubscribe(name); }
};

}

#endif