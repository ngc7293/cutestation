#ifndef CUTE_DATA_VALUE_HH_
#define CUTE_DATA_VALUE_HH_

#include <mutex>

#include <log/log.hh>
#include <topic/subscriber.hh>

namespace cute::data {

class Value {
public:
    virtual double value() const = 0;
    virtual std::chrono::milliseconds timestamp() const = 0;
};

class SimpleDynamicValue : public DynamicValue {
protected:
    using Comparator = std::function<bool(const double& lhs, const double& rhs)>;

public:
    SimpleDynamicValue(const std::string& source, Comparator comparator);

    double value() const override;
    std::chrono::milliseconds timestamp() const override;

    void accept(const std::chrono::milliseconds& when, const double& what) override;

private:
    std::pair<std::chrono::milliseconds, double> data_;
    Comparator comparator_;
};

class MinValue : public SimpleDynamicValue {
public:
    MinValue(const std::string& source);
};

class MaxValue : public SimpleDynamicValue {
public:
    MaxValue(const std::string& source);
};

class LastValue : public SimpleDynamicValue {
public:
    LastValue(const std::string& source);
};

}

#endif