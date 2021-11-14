#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include <cute/data/value_factory.hh>
#include <topic/publisher.hh>

using namespace std::literals::chrono_literals;

TEST(ValueFactory, returns_static_value)
{
    json data = R"(42)"_json;

    cute::data::NumberValue* value = cute::data::ValueFactory::build<double>(data);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->value(), 42);
}

TEST(ValueFactory, returns_max_value)
{
    json data = R"({"source": "cute.data.test", "type": "max"})"_json;

    cute::data::NumberValue* value = cute::data::ValueFactory::build<double>(data);
    EXPECT_NE(value, nullptr);

    topic::Publisher publisher;
    publisher.publish<double>("cute.data.test", -1.0);
    publisher.publish<double>("cute.data.test", 1.0);
    publisher.publish<double>("cute.data.test", 0.5);
    EXPECT_EQ(value->value(), 1.0);
}

TEST(ValueFactory, returns_error_for_nonnumber_nonobject_input)
{
    EXPECT_EQ(cute::data::ValueFactory::build<double>(R"(true)"_json), nullptr);
    EXPECT_EQ(cute::data::ValueFactory::build<double>(R"([""])"_json), nullptr);
    EXPECT_EQ(cute::data::ValueFactory::build<double>(R"(null)"_json), nullptr);
}