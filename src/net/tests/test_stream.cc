#include <gtest/gtest.h>

#include <net/stream.hh>

TEST(stringstream, behaves_identically_but_close_compiles)
{
    net::stringstream ss;
    
    ss << "Test1";
    ss.close();

    EXPECT_EQ(ss.str(), "Test1");
}