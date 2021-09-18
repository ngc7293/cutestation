#ifndef UTIL_TEST_HH_
#define UTIL_TEST_HH_

#include <gtest/gtest.h>

#if (defined _MSC_VER)
#define TEST_WINDOWS(a, b) TEST(a, b)
#define TEST_UNIX(a, b)    TEST(a, DISABLED_##b)
#else
#define TEST_WINDOWS(a, b) TEST(a, DISABLED_##b)
#define TEST_UNIX(a, b)    TEST(a, b)
#endif

#endif