#pragma once

#include <cstring>
#include <string>

//! @file Functions for editing strings

namespace wax {
namespace str {

//! @brief Trim all instances of delimiter from beginning of string.
//
// @param s The string to trim
// @param delim The character to strip, white space if zero.
// @return the trimmed string.
//
std::string & ltrim(std::string &s, const int delim = 0);

//! @brief Trim all instances of delimiter from the end of the string.
//
// @param s The string to trim
// @param delim The character to strip, white space if zero.
// @return the trimmed string.
//
std::string & rtrim(std::string &s, const int delim = 0);

// ! @brief Trim instances of delimiter from beginning and ending of the string.
//
// @param s The string to trim
// @param delim The character to strip, white space if zero.
// @return the trimmed string.
//
static inline const std::string &
trim(std::string &s, const int delim = 0) {
  return ltrim(rtrim(s, delim), delim);
}

static inline const std::string
trim(const std::string &s, const int delim = 0) {
  auto copy = s;
  (void) rtrim(copy, delim);
  (void) ltrim(copy, delim);
  return copy;
}


//! @brief Replace all instances of find with repl.
//
// @param s        String to edit
// @param find     Substring to look for
// @param repl     String to replace it with
// @return the edited string
//
std::string & replace(
  std::string       &s,
  const std::string &find,
  const std::string &repl);


// Overloads helpful in building function templates for use with strings of
// indeterminate type, such as copy_and_twiddle() below.

//! @return Length of the string in bytes.
static inline std::size_t length(const char * const p) { return ::strlen(p); }
static inline std::size_t length(const std::string &s) { return s.length();  }

//! @return Whether string is empty.
static inline bool empty(const char * const p)     { return p && *p == '\0'; }
static inline bool empty(const std::string &s)     { return s.empty();       }

// @return const char * to the string contents.
static inline const char * const
char_ptr(const char * const p) {
  return p;
}
static inline const char * const
char_ptr(const std::string &s) {
  return s.c_str();
}

namespace {

//!
// Python-esque wrapper that copies an input string, which is presumed to be
// immutable in context, and applies the function twiddler to edit the string in
// a particular way.
//
// @return A copy of the original string, edited by twiddler
template <typename string_type, typename func_type>
std::string copy_and_twiddle(string_type && orig, func_type twiddler)
{
  std::string name;

  if (!wax::str::empty(orig)) {
    const auto slen = wax::str::length(orig);
    const decltype(slen) dlen = 2 * slen;

    char copy[dlen];
    (void) std::strncpy(copy, wax::str::char_ptr(orig), slen);
    copy[slen] = '\0';

    name.assign(twiddler(copy));
  }

  return name;
}
} // anonymous namespace

//! @brief Convert string to one line.
//
// If the input string contains line-break characters (carriage return, newline,
// formfeed), remove them and any surrounding horizontal whitespace.  The
// rationale for removing leading and trailing white space on lines is that
// without the vertical alignment suggested by the vertical break, the
// horizontal white space loses its meaning and becomes a liability to most
// output use cases.
//
// @param blob The string to convert
// @return The converted string.
template <typename string_type>
std::string to_line(string_type && blob)
{
  return copy_and_twiddle(
    blob,

    //! @todo This is a brutish, suboptimal implementation.  Do better.
    [](const std::string &s) -> std::string {
      auto lines = split(s, wax::re::vws);
      if (lines.size() < 2)
        return s;
      for (auto & line : lines)
        line = trim(line);
      return join(' ', lines);
    } );
}
} // namespace str
} // namespace wax
