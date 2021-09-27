#include <gtest/gtest.h>

#include <cute/data/series_factory.hh>
#include <cute/data/time_series.hh>
#include <topic/publisher.hh>

using namespace std::literals::chrono_literals;

TEST(TimeSeries, receives_data_from_publishers)
{
    topic::Publisher publisher;
    cute::data::TimeSeries series("cute.data.test.double", 10ms);

    EXPECT_EQ(series.size(), 0);
    publisher.publish<double>("cute.data.test.double", 0.0);
    EXPECT_EQ(series.size(), 1);
}

TEST(TimeSeries, removes_data_older_than_length_before_now)
{
    std::chrono::milliseconds now;
    topic::Publisher publisher;
    cute::data::TimeSeries series("cute.data.test.double", 10ms);

    series.set_now([&now]() { return now; });

    EXPECT_EQ(series.size(), 0);

    now = 100ms;
    publisher.publish<double>("cute.data.test.double", 1.0, now);
    EXPECT_EQ(series.size(), 1);

    now = 111ms;
    publisher.publish<double>("cute.data.test.double", 1.2, now);
    EXPECT_EQ(series.size(), 1);
    now = 112ms;
    publisher.publish<double>("cute.data.test.double", 1.3, now);
    EXPECT_EQ(series.size(), 2);
    EXPECT_EQ(series.front().second, 1.2);
    EXPECT_EQ(series.back().second, 1.3);
}

TEST(SeriesFactory, can_build_valid_series_factory)
{
    const json config = R"({
        "source": "cute.data.test.double",
        "length": 10
    })"_json;

    topic::Publisher publisher;
    std::shared_ptr<cute::data::TimeSeries> series = cute::data::SeriesFactory::build<cute::data::TimeSeries>(config);

    EXPECT_TRUE(static_cast<bool>(series));

    EXPECT_EQ(series->size(), 0);
    publisher.publish<double>("cute.data.test.double", 0.0);
    EXPECT_EQ(series->size(), 1);

    EXPECT_EQ(series->length(), 10ms);
}