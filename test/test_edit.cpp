#include "gtest/gtest.h"

#include <str/edit>

class trim_tests : public ::testing::Test {};

TEST_F(trim_tests, init)
{
  SUCCEED();
}

TEST_F(trim_tests, ltrim_empty)
{
  std::string s("");
  ASSERT_EQ(wax::str::ltrim(s), s);
}

TEST_F(trim_tests, ltrim_none)
{
  std::string s("test");
  ASSERT_EQ(wax::str::ltrim(s), "test");
}

TEST_F(trim_tests, ltrim_only_delimiters)
{
  std::string s("   ");
  ASSERT_EQ(wax::str::ltrim(s), "");
}

TEST_F(trim_tests, ltrim_right_delimiters)
{
  std::string s("test   ");
  ASSERT_EQ(wax::str::ltrim(s), "test   ");
}

TEST_F(trim_tests, ltrim_embedded_delimiters)
{
  std::string s("test 42");
  ASSERT_EQ(wax::str::ltrim(s), "test 42");
  s = " test 42";
  ASSERT_EQ(wax::str::ltrim(s), "test 42");
}

TEST_F(trim_tests, ltrim_white_space)
{
  std::string s("\r\t\f\n test");
  ASSERT_EQ(wax::str::ltrim(s), "test");
}

TEST_F(trim_tests, ltrim_custom_delimiter)
{
  std::string s("--test");
  ASSERT_EQ(wax::str::ltrim(s, '-'), "test");
}


TEST_F(trim_tests, rtrim_empty)
{
  std::string s("");
  ASSERT_EQ(wax::str::rtrim(s), s);
}

TEST_F(trim_tests, rtrim_none)
{
  std::string s("test");
  ASSERT_EQ(wax::str::rtrim(s), "test");
}

TEST_F(trim_tests, rtrim_only_delimiters)
{
  std::string s("   ");
  ASSERT_EQ(wax::str::rtrim(s), "");
}

TEST_F(trim_tests, rtrim_left_delimiters)
{
  std::string s("   test");
  ASSERT_EQ(wax::str::rtrim(s), "   test");
}

TEST_F(trim_tests, rtrim_embedded_delimiters)
{
  std::string s("test 42");
  ASSERT_EQ(wax::str::rtrim(s), "test 42");
  s = "test 42 ";
  ASSERT_EQ(wax::str::rtrim(s), "test 42");
}

TEST_F(trim_tests, rtrim_white_space)
{
  std::string s("test\r\t\f\n ");
  ASSERT_EQ(wax::str::rtrim(s), "test");
}

TEST_F(trim_tests, rtrim_custom_delimiter)
{
  std::string s("test--");
  ASSERT_EQ(wax::str::rtrim(s, '-'), "test");
}


TEST_F(trim_tests, trim_empty)
{
  std::string s("");
  ASSERT_EQ(wax::str::trim(s), s);
}

TEST_F(trim_tests, trim_none)
{
  std::string s("test");
  ASSERT_EQ(wax::str::trim(s), "test");
}

TEST_F(trim_tests, trim_only_delimiters)
{
  std::string s("   ");
  ASSERT_EQ(wax::str::trim(s), "");
}

TEST_F(trim_tests, trim_left_delimiters)
{
  std::string s("   test");
  ASSERT_EQ(wax::str::trim(s), "test");
}

TEST_F(trim_tests, trim_right_delimiters)
{
  std::string s("test   ");
  ASSERT_EQ(wax::str::trim(s), "test");
}

TEST_F(trim_tests, trim_all_delimiters)
{
  std::string s("   test   ");
  ASSERT_EQ(wax::str::trim(s), "test");
}

TEST_F(trim_tests, trim_embedded_delimiters)
{
  std::string s("test 42");
  ASSERT_EQ(wax::str::trim(s), "test 42");
  s = "test 42 ";
  ASSERT_EQ(wax::str::trim(s), "test 42");
  s = " test 42";
  ASSERT_EQ(wax::str::trim(s), "test 42");
  s = " test 42 ";
  ASSERT_EQ(wax::str::trim(s), "test 42");
}

TEST_F(trim_tests, trim_custom_delimiter)
{
  std::string s("--test--");
  ASSERT_EQ(wax::str::trim(s, '-'), "test");
}


class replace_tests : public ::testing::Test {};

TEST_F(replace_tests, init)
{
  SUCCEED();
}

TEST_F(replace_tests, empty_src)
{
  std::string s("");
  ASSERT_EQ(wax::str::replace(s, "test", "42"), "");
}

TEST_F(replace_tests, empty_find)
{
  std::string s("test 42");
  ASSERT_EQ(wax::str::replace(s, "", "foo"), "test 42");
}

TEST_F(replace_tests, empty_repl)
{
  std::string s("test 42 test");
  ASSERT_EQ(wax::str::replace(s, "42", ""), "test  test");
}

TEST_F(replace_tests, prefix)
{
  std::string s("test 42");
  ASSERT_EQ(wax::str::replace(s, "test", "foo"), "foo 42");
}

TEST_F(replace_tests, suffix)
{
  std::string s("test 42");
  ASSERT_EQ(wax::str::replace(s, "42", "0"), "test 0");
}

TEST_F(replace_tests, middle)
{
  std::string s("test foo 42");
  ASSERT_EQ(wax::str::replace(s, "foo ", ""), "test 42");
}

TEST_F(replace_tests, multiple)
{
  std::string s("test 42 42 test 42 42 test");
  ASSERT_EQ(wax::str::replace(s, " 42", ""), "test test test");
}


class symmetry_tests : public ::testing::Test
{
 public:
  const char *s = "Now is the time";
};

TEST_F(symmetry_tests, init)
{
  SUCCEED();
}

TEST_F(symmetry_tests, length)
{
  ASSERT_EQ(wax::str::length(s), wax::str::length(std::string(s)));
  ASSERT_NE(wax::str::length(s), 0);
}

TEST_F(symmetry_tests, empty)
{
  const char *s = "";
  ASSERT_TRUE(wax::str::empty(s));
  ASSERT_TRUE(wax::str::empty(std::string(s)));
}

TEST_F(symmetry_tests, pointer)
{
  ASSERT_EQ(wax::str::char_ptr(s), s);
  ASSERT_NE(wax::str::char_ptr(std::string(s)), nullptr);
}
