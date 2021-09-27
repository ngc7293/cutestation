#include <gtest/gtest.h>

#include <cmath>

#include <cute/data/dynamic_value.hh>
#include <cute/data/average_value.hh>
#include <topic/publisher.hh>

using namespace std::literals::chrono_literals;


TEST(MinValue, selects_minimum_value)
{
    topic::Publisher publisher;
    cute::data::MinValue value("cute.data.test.double");

    EXPECT_EQ(value.value(), 0);

    // First value is always selected
    publisher.publish<double>("cute.data.test.double", 1.0, 10ms);
    EXPECT_EQ(value.value(), 1.0);

    publisher.publish<double>("cute.data.test.double", 0.2, 20ms);
    publisher.publish<double>("cute.data.test.double", 4.2, 21ms);
    EXPECT_EQ(value.value(), 0.2);

    publisher.publish<double>("cute.data.test.double", -1.0, 30ms);
    publisher.publish<double>("cute.data.test.double", -0.9, 31ms);
    EXPECT_EQ(value.value(), -1.0);
    EXPECT_EQ(value.timestamp(), 30ms);
}

TEST(MaxValue, selects_maximum_value)
{
    topic::Publisher publisher;
    cute::data::MaxValue value("cute.data.test.double");

    EXPECT_EQ(value.value(), 0);

    // First value is always chosen
    publisher.publish<double>("cute.data.test.double", -1.0, 10ms);
    EXPECT_EQ(value.value(), -1.0);

    publisher.publish<double>("cute.data.test.double", 4.2, 20ms);
    publisher.publish<double>("cute.data.test.double", 0.2, 21ms);
    EXPECT_EQ(value.value(), 4.2);
    EXPECT_EQ(value.timestamp(), 20ms);
}

TEST(LastValue, selects_last_value)
{
    topic::Publisher publisher;
    cute::data::LastValue value("cute.data.test.double");

    EXPECT_EQ(value.value(), 0);

    // First value is always chosen
    publisher.publish<double>("cute.data.test.double", -1.0, 10ms);
    EXPECT_EQ(value.value(), -1.0);

    publisher.publish<double>("cute.data.test.double", 4.2, 20ms);
    publisher.publish<double>("cute.data.test.double", 2.2, 21ms);
    EXPECT_EQ(value.value(), 2.2);
    EXPECT_EQ(value.timestamp(), 21ms);
}

TEST(RollingAverage, returns_rolling_average)
{
    topic::Publisher publisher;
    cute::data::RollingAverageValue value("cute.data.test.double", 20ms);

    auto now = 0ms;
    value.series().set_now([&] { return now; });

    EXPECT_EQ(value.value(), 0);

    publisher.publish<double>("cute.data.test.double", -1.0, ++now);
    publisher.publish<double>("cute.data.test.double", 0.0, ++now);
    publisher.publish<double>("cute.data.test.double", 1.0, ++now);
    publisher.publish<double>("cute.data.test.double", 2.0, ++now);
    EXPECT_EQ(value.value(), 0.5);
    EXPECT_EQ(value.timestamp(), 4ms);
}