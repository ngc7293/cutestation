#ifndef TOPIC_PUBLISHER_HH_
#define TOPIC_PUBLISHER_HH_

#include <any>
#include <chrono>
#include <memory>
#include <string>
#include <utility>

#include "type.hh"

namespace topic {

class Publisher final {
public:
    Publisher();
    virtual ~Publisher();

public:
    template <typename T>
    bool publish(const std::string& name, const T& value, const topic::time& time = std::chrono::duration_cast<topic::time>(std::chrono::high_resolution_clock::now().time_since_epoch()))
    {
        return publish_generic(name, time, std::any(value));
    }

private:
    bool publish_generic(const std::string& name, const topic::time& time, const std::any& value) const;

private:
    struct Priv;
    std::unique_ptr<Priv> d_;
};

}

#endif