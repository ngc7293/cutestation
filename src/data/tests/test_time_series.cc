#include <gtest/gtest.h>

#include <data/series_factory.hh>
#include <data/time_series.hh>
#include <topic/publisher.hh>

TEST(TimeSeries, receives_data_from_publishers)
{
    topic::Publisher publisher;
    cute::data::TimeSeries<double> series("cute.data.test.double", 10);

    EXPECT_EQ(series.size(), 0);
    publisher.publish<double>("cute.data.test.double", 0.0f);
    EXPECT_EQ(series.size(), 1);
}

TEST(TimeSeries, removes_data_older_than_length_before_now)
{
    uint64_t now;
    topic::Publisher publisher;
    cute::data::TimeSeries<double> series("cute.data.test.double", 10);

    series.set_now([&now]() { return now; });

    EXPECT_EQ(series.size(), 0);

    now = 100;
    publisher.publish<double>("cute.data.test.double", 1.0, topic::time(100));
    EXPECT_EQ(series.size(), 1);

    now = 111;
    publisher.publish<double>("cute.data.test.double", 1.2, topic::time(111));
    EXPECT_EQ(series.size(), 1);
    now = 112;
    publisher.publish<double>("cute.data.test.double", 1.3, topic::time(112));
    EXPECT_EQ(series.size(), 2);
    EXPECT_EQ(series.first(), 1.2);
    EXPECT_EQ(series.last(), 1.3);
}

TEST(SeriesFactory, can_build_valid_series_factory)
{
    const json config = R"({
        "source": "cute.data.test.double",
        "length": 10
    })"_json;

    topic::Publisher publisher;
    std::shared_ptr<cute::data::TimeSeries<double>> series = cute::data::SeriesFactory::build<cute::data::TimeSeries<double>>(config);

    EXPECT_TRUE((bool) series);

    EXPECT_EQ(series->size(), 0);
    publisher.publish<double>("cute.data.test.double", 0.0f);
    EXPECT_EQ(series->size(), 1);

    EXPECT_EQ(series->length(), 10);
}