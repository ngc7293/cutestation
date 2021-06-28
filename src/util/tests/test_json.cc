#include <gtest/gtest.h>

#include <util/json.hh>

const json TEST_JSON = R"(
{
    "name": "Test JSON",
    "required": true,
    "life": 40,
    "phi": 1.618,
    "ints": [-1, 2, -3],
    "uints": [1, 2, 3],
    "strings": ["alpha", "bravo", "charlie", "delta"],
    "empty": [],
    "mixed": ["alpha", 2, 3.1]
}
)"_json;

TEST(json, validates_returns_correct_values_on_success)
{
    std::string name, option;
    bool required;
    int life;
    double phi;

    bool success = util::json::validate(test_info_->test_suite_name(), TEST_JSON,
        util::json::required { name, "name" },
        util::json::required { required, "required" },
        util::json::required { life, "life" },
        util::json::optional { phi, "phi", 3.1415 },
        util::json::optional { option, "option", "facultative" }
    );

    EXPECT_TRUE(success);
    EXPECT_EQ(name, "Test JSON");
    EXPECT_EQ(required, true);
    EXPECT_EQ(life, 40);
    EXPECT_EQ(phi, 1.618);
    EXPECT_EQ(option, "facultative");
}

TEST(json, parses_arrays_correctly)
{
    std::vector<std::string> strings;
    std::vector<int> ints;
    std::vector<unsigned> uints;

    bool success = util::json::validate(test_info_->test_suite_name(), TEST_JSON,
        util::json::required { strings, "strings" },
        util::json::required { ints, "ints" },
        util::json::required { uints, "uints" }
    );

    EXPECT_TRUE(success);
    EXPECT_EQ(strings.size(), 4);
    EXPECT_EQ(ints.size(), 3);
    EXPECT_EQ(uints.size(), 3);
}

TEST(json, tolerates_empty_array)
{
    std::vector<unsigned> list;

    bool success = util::json::validate(test_info_->test_suite_name(), TEST_JSON,
        util::json::required { list, "empty" }
    );

    EXPECT_TRUE(success);
    EXPECT_EQ(list.size(), 0);
}

TEST(json, does_not_tolerate_mixed_arrays)
{
    std::vector<std::string> list;

    bool success = util::json::validate(test_info_->test_suite_name(), TEST_JSON,
        util::json::required { list, "mixed" }
    );

    EXPECT_FALSE(success);
    EXPECT_EQ(list.size(), 0);
}

TEST(json, validates_returns_false_on_failure)
{
    std::string name;
    int c;

    bool success = util::json::validate(test_info_->test_suite_name(), TEST_JSON,
        util::json::required(name, "name"),
        util::json::required(c, "c")
    );

    EXPECT_FALSE(success);
}
