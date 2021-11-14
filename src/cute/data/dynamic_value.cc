#include <mutex>

#include <log/log.hh>
#include <topic/subscriber.hh>

#include "dynamic_value.hh"

using namespace std::literals::chrono_literals;

namespace cute::data {

template<typename Type>
DynamicValue<Type>::DynamicValue(const std::string& source)
{
    if (!subscriber_.subscribe<Type>(source, [this](const auto& t, const Type& v) {
        accept(t, v);
    })) {
        logging::err("TimeSeries") << "Could not subscribe to topic '" << source << "' with type double" << logging::endl;
    }
}

template<typename Type>
SimpleDynamicValue<Type>::SimpleDynamicValue(const std::string& source, Comparator comparator)
    : DynamicValue<Type>(source)
    , comparator_(comparator)
{
}

template<typename Type>
Type SimpleDynamicValue<Type>::value() const
{
    return data_.second;
}

template<typename Type>
std::chrono::milliseconds SimpleDynamicValue<Type>::timestamp() const
{
    return data_.first;
}

template<typename Type>
void SimpleDynamicValue<Type>::accept(const std::chrono::milliseconds& when, const Type& what)
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

template<typename Type>
LastValue<Type>::LastValue(const std::string& source)
    : SimpleDynamicValue<Type>(source, [] (const auto& , const auto& ) { return true; })
{
}

template class LastValue<double>;
template class LastValue<int>;
template class LastValue<std::string>;

} // namespaces