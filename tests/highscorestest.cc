#include <gtest/gtest.h>

TEST(First, FirstTest) {
  EXPECT_STRNE("hello", "world");

  EXPECT_EQ(7 * 6, 42);
}
