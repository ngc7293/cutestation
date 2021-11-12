#include <gtest/gtest.h>

#include <util/geo.hh>

TEST(geo, bearing)
{
    EXPECT_EQ(0, util::geo::bearing({0.0, 0.0}, {90.0, 0.0}));
    EXPECT_EQ(90, util::geo::bearing({0.0, 0.0}, {0.0, 90.0}));
    EXPECT_NEAR(52.907, util::geo::bearing({40.7486, -73.9864}, {50.1234, 0.0}), 0.001);
    EXPECT_NEAR(260.277, util::geo::bearing({-88.66, 44.22}, {11.33, -55.77}), 0.001);
}

TEST(geo, distance)
{
    EXPECT_NEAR(11292888, util::geo::distance({-88.66, 44.22}, {11.33, -55.77}), 1);
    EXPECT_NEAR(9480660, util::geo::distance({35.6544, 139.74477}, {21.4225, 39.8261}), 1);
}