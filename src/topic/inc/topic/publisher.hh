#ifndef TOPIC_PUBLISHER_HH_
#define TOPIC_PUBLISHER_HH_

#include <any>
#include <chrono>
#include <memory>
#include <string>
#include <utility>

namespace topic {

class Publisher {
public:
    Publisher();
    virtual ~Publisher();

protected:
    template <typename T>
    bool publish(const std::string& name, const T& value, const std::chrono::nanoseconds& time = std::chrono::high_resolution_clock::now().time_since_epoch())
    {
        return publish_generic(name, time, std::any(value));
    }

private:
    bool publish_generic(const std::string& name, const std::chrono::nanoseconds& time, const std::any& value) const;

private:
    struct Priv;
    std::unique_ptr<Priv> d_;
};

}

#endif