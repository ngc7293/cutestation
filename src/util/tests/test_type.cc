#include <gtest/gtest.h>

#include <util/type.hh>

TEST(type, should_return_correct_demangled_name)
{
    /* Testing key types used in CuteStation*/
    EXPECT_EQ(std::string(util::type::name<double>()), "double");
    EXPECT_EQ(std::string(util::type::name<int>()), "int");
    EXPECT_EQ(std::string(util::type::name<bool>()), "bool");
    EXPECT_EQ(std::string(util::type::name<std::string>()), "string");
}