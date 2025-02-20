#include "gtest/gtest.h"

#include "./str/impl/cstr.hpp"

class cstr_tests : public ::testing::Test
{
 public:
  wax::__cstr::less  lesser;  // ...of two evils.
  wax::__cstr::equal equator;
};

TEST_F(cstr_tests, init)
{
  SUCCEED();
}

TEST_F(cstr_tests, less_succeed)
{
  ASSERT_TRUE(lesser("A", "B"));
  ASSERT_TRUE(lesser("AAAAA", "AAAAB"));
}

TEST_F(cstr_tests, less_fail)
{
  ASSERT_FALSE(lesser("B", "A"));
  ASSERT_FALSE(lesser("AAAAB", "AAAAA"));
}

TEST_F(cstr_tests, less_empty)
{
  ASSERT_FALSE(lesser("A", ""));
}

TEST_F(cstr_tests, less_equal)
{
  ASSERT_FALSE(lesser("A", "A"));
}

TEST_F(cstr_tests, equal_succeed)
{
  ASSERT_TRUE(equator("A", "A"));
  ASSERT_TRUE(equator("AAAAA", "AAAAA"));
}

TEST_F(cstr_tests, equal_fail)
{
  ASSERT_FALSE(equator("A", "B"));
  ASSERT_FALSE(equator("AAAAB", "AAAAA"));
}

TEST_F(cstr_tests, equal_empty)
{
  ASSERT_TRUE(equator("", ""));
}
