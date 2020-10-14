#include <gtest/gtest.h>

#include <data/time_series.hh>
#include <topic/mock.hh>

TEST(TimeSeries, receives_data_from_publishers)
{
    topic::MockPublisher publisher;
    cute::data::TimeSeries<double> series("cute.data.test.double", 10);

    EXPECT_EQ(series.size(), 0);
    publisher.callPublish<double>("cute.data.test.double", 0.0f);
    EXPECT_EQ(series.size(), 1);
}

TEST(TimeSeries, removes_data_older_than_length_before_now)
{
    uint64_t now;
    topic::MockPublisher publisher;
    cute::data::TimeSeries<double> series("cute.data.test.double", 10);

    series.set_now([&now]() { return now; });

    EXPECT_EQ(series.size(), 0);

    now = 100;
    publisher.callPublish<double>("cute.data.test.double", 0.0f, topic::time(100));
    EXPECT_EQ(series.size(), 1);

    now = 111;
    publisher.callPublish<double>("cute.data.test.double", 0.0f, topic::time(111));
    EXPECT_EQ(series.size(), 1);
    now = 112;
    publisher.callPublish<double>("cute.data.test.double", 0.0f, topic::time(112));
    EXPECT_EQ(series.size(), 2);
}