#include "gtest/gtest.h"

#include <string>

#include "../src/str/dict"
#include "../src/str/parse"

class split_tests : public ::testing::Test
{
 public:

  const std::string s_empty { "" };
  const wax::svec a_empty {};

  const std::string s1 {"Attack at dawn"};
  const wax::svec a1 {"Attack", "at", "dawn"};
  const wax::svec all1 {s1};
  const wax::svec ak {"Attac", " at dawn"};

  const std::string s2 {"ABC"};
  const wax::svec a2 {"A", "B", "C" };

  const std::string s3 {"line 1\r\nline 2\nline 3\v"};
  const wax::svec a3 {"line 1", "line 2", "line 3"};
};

TEST_F(split_tests, init)
{
  SUCCEED();
}

TEST_F(split_tests, empty_string)
{
  ASSERT_EQ(wax::str::split(s_empty), a_empty);
  ASSERT_EQ(wax::str::split(s_empty, ' '), a_empty);
}

TEST_F(split_tests, empty_regex)
{
  ASSERT_EQ(wax::str::split(s2, s_empty), a2 );
}

TEST_F(split_tests, horizontal_whitespace)
{
  ASSERT_EQ(wax::str::split(s1), a1);
  ASSERT_EQ(wax::str::split(s1, ' '), a1);
}

TEST_F(split_tests, vertical_whitespace)
{
  ASSERT_EQ(wax::str::split(s3, wax::re::vws), a3);
}

TEST_F(split_tests, failed_match)
{
  ASSERT_EQ(wax::str::split(s1, "[q]"), all1);
  ASSERT_EQ(wax::str::split(s1, 'q'), all1);
}

TEST_F(split_tests, arbitrary_char)
{
  ASSERT_EQ(wax::str::split(s1, 'k'), ak);
  ASSERT_EQ(wax::str::split(s1, "[k]"), ak);
}
