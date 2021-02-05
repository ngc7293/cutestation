#include <gtest/gtest.h>

#include <net/stream.hh>

TEST(stringstream, behaves_identically_but_close_compiles)
{
    net::stringstream ss;
    net::closeable& c = ss;
    
    c << "Test1";
    c.close();

    EXPECT_EQ(ss.str(), "Test1");
}