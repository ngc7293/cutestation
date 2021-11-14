#ifndef CUTE_DATA_DYNAMICVALUE_HH_
#define CUTE_DATA_DYNAMICVALUE_HH_

#include <mutex>

#include <cute/data/value.hh>
#include <log/log.hh>
#include <topic/subscriber.hh>

namespace cute::data {

template<typename Type>
class DynamicValue: public Value<Type> {
public:
    DynamicValue(const std::string& source);
    virtual ~DynamicValue();

protected:
    virtual void accept(const std::chrono::milliseconds& when, const Type& what) = 0;

private:
    topic::Subscriber subscriber_;
};

template<typename Type>
class SimpleDynamicValue: public DynamicValue<Type> {
protected:
    using Comparator = std::function<bool(const Type& lhs, const Type& rhs)>;

public:
    SimpleDynamicValue(const std::string& source, Comparator comparator);

    Type value() const override;
    std::chrono::milliseconds timestamp() const override;

protected:
    void accept(const std::chrono::milliseconds& when, const Type& what) override;

private:
    std::pair<std::chrono::milliseconds, Type> data_;
    Comparator comparator_;
};

class MinValue : public SimpleDynamicValue<double> {
public:
    MinValue(const std::string& source);
};

class MaxValue : public SimpleDynamicValue<double> {
public:
    MaxValue(const std::string& source);
};

template<typename Type>
class LastValue : public SimpleDynamicValue<Type> {
public:
    LastValue(const std::string& source);
};

}

#endif