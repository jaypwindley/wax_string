#include <ctime>

#include "gtest/gtest.h"

#include "./str/compose"
#include "./str/dict"

class join_tests : public ::testing::Test
{
 public:
  wax::svec none   {};
  wax::svec single {"foo"};
  wax::svec many   {"tom", "dick", "harry"};
};

TEST_F(join_tests, init)
{
  SUCCEED();
}

TEST_F(join_tests, empty)
{
  // Empyt iterable = empty string
  ASSERT_EQ(wax::str::join(' ', none), "");
  ASSERT_EQ(wax::str::join(" ", none), "");
  ASSERT_EQ(wax::str::join("--", none), "");
}

TEST_F(join_tests, single)
{
  // One-element iterables don't have the delimiter.
  ASSERT_EQ(wax::str::join(' ', single), single[0]);
  ASSERT_EQ(wax::str::join(" ", single), single[0]);
  ASSERT_EQ(wax::str::join("--", single), single[0]);
}

TEST_F(join_tests, multiple)
{
  ASSERT_EQ(wax::str::join(' ', many), "tom dick harry");
  ASSERT_EQ(wax::str::join(" ", many), "tom dick harry");
  ASSERT_EQ(wax::str::join("--", many), "tom--dick--harry");
}


class time_tests : public ::testing::Test
{
 public:
  ::time_t when = 543345609;
};

TEST_F(time_tests, init)
{
  SUCCEED();
}

TEST_F(time_tests, utime)
{
  // UTC
  ASSERT_EQ(wax::utime(when), "1987-03-21 17:20:09");
}

TEST_F(
  time_tests,
#ifdef _WIN32
  DISABLED_fntime
#else
  fntime
#endif
  )
{
  // File name (local time), can't have any characters that file systems gag on,
  // on any operating system.  Windows can't have colons, for example.
  ASSERT_EQ(wax::fntime(when), "1987-03-21_10h20m09s");
}

TEST_F(
  time_tests,
#ifdef _WIN32
  DISABLED_ltime
#else
  ltime
#endif
  )
{
  ASSERT_EQ(wax::ltime(when), "1987-03-21 10:20:09");
}
