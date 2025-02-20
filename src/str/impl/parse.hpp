#pragma once

#include <string>

namespace wax {

// Handy regular expressions to use in parsing.
namespace re {
static const char * const ws = "[[:space:]]+";    ///< All white space
static const char * const vws = "[^[:print:]]+";  ///< Just vertical white space
} // namespace re

namespace str {

//! @brief Split a string according to a regular expression.
//
//  Prefixes in s that match the regular expression are ignored.  The first
//  element in the return value is the first substring that does not match the
//  regex.
//
//  @param s        The string to split
//
//  @param regex    The Extended Posix Regular Expression to use to split the string.
//                  Defaults to white space.  If empty, the string is split into
//                  individual characters.
//
// @return Vector of tokens from the string
//
// @todo Templated version that can take different string representations and
// different output vector representations.
svec split(const std::string &s, const std::string &regex = re::ws);


//! @brief Split a string according to a single delimiter character
//
// Use this version when the delimiter is a single character, a common case.
// Adjacent sequences of delimiter characters are treated as one delimiter.
// Leading delimiter is ignored; the first element in the return value is the
// first substring of s that starts with a non-delimiter character.
//
// @param s        The string to split
// @param delim    The delimiter character.
//
// @return Vector of tokens from the string
svec split(const std::string &s, const char delim);
} // namespace str

namespace __priv {
static inline bool is_digit(const char ch)
{
  /* High nybble must be 0x30 */
  if ((ch & 0xf0) != 0x30)
    return false;

  /* High nybble, high bit is zero --> digit.  If not, middle two bits must be zero. */
  if (((ch & 0x08) != 0) && ((ch & 0x06) != 0))
    return false;

  return true;
}
} // namespace __priv

//! @return true if string is composed entirely of digits
// @param str String to test
//
// @todo Templatize this with the string abstraction macros
static inline bool is_digits(const std::string &str)
{
  if (str.empty())
    return false;
  for (const auto ch : str)
    if ( ! __priv::is_digit(ch))
      return false;
  return true;
}


static inline bool is_digits(const char * const str)
{
  if ( ! str || ! *str)
    return false;
  for (auto p = str; *p; ++p)
    if ( ! __priv::is_digit(*p))
      return false;
  return true;
}

} // namespace wax
