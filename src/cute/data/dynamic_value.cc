#include <mutex>

#include <log/log.hh>
#include <topic/subscriber.hh>

#include "dynamic_value.hh"

using namespace std::literals::chrono_literals;

namespace cute::data {

DynamicValue::DynamicValue(const std::string& source)
{
    if (!subscriber_.subscribe<double>(source, [this](const auto& t, const double& v) {
        accept(t, v);
    })) {
        logging::err("TimeSeries") << "Could not subscribe to topic '" << source << "' with type double" << logging::endl;
    }
}

SimpleDynamicValue::SimpleDynamicValue(const std::string& source, Comparator comparator)
    : DynamicValue(source)
    , comparator_(comparator)
{
}

double SimpleDynamicValue::value() const
{
    return data_.second;
}

std::chrono::milliseconds SimpleDynamicValue::timestamp() const
{
    return data_.first;
}

void SimpleDynamicValue::accept(const std::chrono::milliseconds& when, const double& what)
{
    if (comparator_(what, data_.second)) {
        data_ = {when, what};
    } else if (data_.first == 0ms) {
        data_ = {when, what};
    }
}

MinValue::MinValue(const std::string& source)
    : SimpleDynamicValue(source, [] (const auto& lhs, const auto& rhs) { return lhs < rhs; })
{
}

MaxValue::MaxValue(const std::string& source)
    : SimpleDynamicValue(source, [] (const auto& lhs, const auto& rhs) { return lhs > rhs; })
{
}

LastValue::LastValue(const std::string& source)
    : SimpleDynamicValue(source, [] (const auto& , const auto& ) { return true; })
{
}

} // namespaces