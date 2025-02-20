#include <cstdarg>
#include <cstring>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "./str/format"

class sprintf_tests : public ::testing::Test {};

TEST_F(sprintf_tests, init)
{
  SUCCEED();
}

TEST_F(sprintf_tests, empty)
{
  ASSERT_EQ(wax::sprintf(""), "");
}

TEST_F(sprintf_tests, simple)
{
  ASSERT_EQ(wax::sprintf("test"), "test");
}

// We don't specifically test all the functionality of the printf(3)-like
// behavior.  It all depends on vsprintf(3), which either works or it doesn't.
// We don't look for bugs in vsprintf(3).  The real test is just to see whether
// the standard-argument lists are built correctly before they get sent to
// vsprintf(3).

TEST_F(sprintf_tests, string)
{
  ASSERT_EQ(wax::sprintf("test %s", "foo"), "test foo");
}

TEST_F(sprintf_tests, number)
{
  ASSERT_EQ(wax::sprintf("test %d", 42), "test 42");
}

TEST_F(sprintf_tests, multiple)
{
  ASSERT_EQ(wax::sprintf("test %s %d", "foo", 42), "test foo 42");
}


class printf_ctor_tests : public ::testing::Test
{
 public:
  const char * expand_to_char_ptr(wax::types::printf args)
  {
    static const char *safe_return = nullptr;
    safe_return = args;
    return safe_return;
  }

  std::string expand_to_string(wax::types::printf args)
  {
    return args;
  }
};

TEST_F(printf_ctor_tests, init)
{
  SUCCEED();
}

TEST_F(printf_ctor_tests, empty)
{
  ASSERT_EQ(expand_to_string(""), "");
  ASSERT_EQ(std::strcmp(expand_to_char_ptr(""), ""), 0);
}

TEST_F(printf_ctor_tests, single)
{
  ASSERT_EQ(expand_to_string( {"test %d", 42} ), "test 42");
  ASSERT_EQ(std::strcmp(expand_to_char_ptr( {"test %d", 42} ), "test 42"), 0);
}

TEST_F(printf_ctor_tests, multiple)
{
  ASSERT_EQ(expand_to_string( {"test %s %d", "foo", 42} ), "test foo 42");
  ASSERT_EQ(std::strcmp(
              expand_to_char_ptr( {"test %s %d", "foo", 42} ),
              "test foo 42"),
            0);
}


class ostream_tests : public ::testing::Test
{
 public:
  std::ostringstream stream;
};

TEST_F(ostream_tests, init)
{
  SUCCEED();
}

TEST_F(ostream_tests, empty)
{
  ASSERT_EQ(stream.str(), "");
  stream << wax::format("");
  ASSERT_EQ(stream.str(), "");
}

TEST_F(ostream_tests, format)
{
  stream << wax::format("test");
  ASSERT_EQ(stream.str(), "test");
}

TEST_F(ostream_tests, single)
{
  stream << wax::format("test %d", 42);
  ASSERT_EQ(stream.str(), "test 42");
}

TEST_F(ostream_tests, multiple)
{
  stream << wax::format("test %s %d", "foo", 42);
  ASSERT_EQ(stream.str(), "test foo 42");
}

TEST_F(ostream_tests, chained)
{
  stream << wax::format("test %s", "foo") << wax::format(" %d", 42);
  ASSERT_EQ(stream.str(), "test foo 42");
}
