#include <gtest/gtest.h>

#include <cute/widgets/range_mapping.hh>

TEST(RangeMapping, should_build_correctly)
{
    const nlohmann::json config = R"({
        "0~1": { "displayFormat": "Alpha" },
        "1~3": { "displayFormat": "Bravo %s", "color": "white", "background": "black" },
        "4~5": { "displayFormat": "Charlie" }
    })"_json;

    auto mappings = cute::widgets::RangeMapping<int>::buildAll(config);

    ASSERT_EQ(mappings.size(), 3);
    EXPECT_EQ(mappings[0].displayFormat, "Alpha");
    EXPECT_EQ(mappings[0].low, 0);
    EXPECT_EQ(mappings[0].high, 1);
    EXPECT_EQ(mappings[0].color, "");
    EXPECT_EQ(mappings[0].backgroundColor, "");

    EXPECT_EQ(mappings[1].displayFormat, "Bravo %s");
    EXPECT_EQ(mappings[1].low, 1);
    EXPECT_EQ(mappings[1].high, 3);
    EXPECT_EQ(mappings[1].color, "white");
    EXPECT_EQ(mappings[1].backgroundColor, "black");

    EXPECT_EQ(mappings[2].low, 4);
    EXPECT_EQ(mappings[2].high, 5);
}

TEST(RangeMapping, should_build_correctly_with_infinities)
{
    {
        auto mappings = cute::widgets::RangeMapping<int>::buildAll(R"({
            "~1": { "displayFormat": "Alpha" },
            "1~": { "displayFormat": "Bravo" }
        })"_json);

        ASSERT_EQ(mappings.size(), 2);

        EXPECT_EQ(mappings[0].low, std::numeric_limits<int>::min());
        EXPECT_EQ(mappings[0].high, 1);

        EXPECT_EQ(mappings[1].low, 1);
        EXPECT_EQ(mappings[1].high, std::numeric_limits<int>::max());
    }
    {
        auto mappings = cute::widgets::RangeMapping<int>::buildAll(R"({
            "~": { "displayFormat": "Alpha" }
        })"_json);

        ASSERT_EQ(mappings.size(), 1);
        EXPECT_EQ(mappings[0].low, std::numeric_limits<int>::min());
        EXPECT_EQ(mappings[0].high, std::numeric_limits<int>::max());
    }
}

TEST(RangeMapping, should_not_build_with_overlaps)
{
    {
        const nlohmann::json config = R"({
            "0~5": { "displayFormat": "Alpha" },
            "1~2": { "displayFormat": "Bravo" }
        })"_json;

        auto mappings = cute::widgets::RangeMapping<int>::buildAll(config);
        EXPECT_EQ(mappings.size(), 0);
    }
    {
        const nlohmann::json config = R"({
            "0~": { "displayFormat": "Alpha" },
            "1~2": { "displayFormat": "Bravo" }
        })"_json;

        auto mappings = cute::widgets::RangeMapping<int>::buildAll(config);
        EXPECT_EQ(mappings.size(), 0);
    }
    {
        const nlohmann::json config = R"({
            "~": { "displayFormat": "Alpha" },
            "~1": { "displayFormat": "Bravo" }
        })"_json;

        auto mappings = cute::widgets::RangeMapping<int>::buildAll(config);
        EXPECT_EQ(mappings.size(), 0);
    }
}