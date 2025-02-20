#pragma once

#include <cstdarg>
#include <string>
#include <ostream>

//! @file Functions for formatting strings

namespace wax {

//! @brief vsprintf(3)-like function that returns a formatted std::string.
// @param fmt printf(3) format string
// @param valist std::args list.
// @return std::string containing the arguments formatted as if by vsprintf(3).
std::string vsprintf(const char *fmt, std::va_list valist);

//! @brief xprintf(3)-like function that returns a formatted std::string.
// @param fmt printf(3) format string
// @param ... additional arguments
// @return std::string containing the arguments formatted as if by sprintf(3).
static inline std::string sprintf(const char * const fmt, ...)
{
  std::string s;
  std::va_list args;
  va_start(args, fmt);
  s = wax::vsprintf(fmt, args);
  va_end(args);
  return s;
}

namespace types {

//!
// @class printf
//
// Class wrapper around sprintf and vsprintfs.  Any function that wants to take
// printf()-style arguments can simply take an argument of this class and apply
// constructor-overload semantics at the call site.  Within the function the
// argument is implicitly convertible both to std::string and const char *.
//
//     void foomatic(wax::types::printf args)
//     {
//         do_something(strlen(args)); // Converts to const char *
//         std::cout << args.substr(0, trunc); // Converts to std::string
//     }
//
//     ...
//
//     // Call site, braced arg list goes to constructor.
//     foomatic( { "%s: %s=%d", "prefix", key, value } );
//
class printf
{
 public:
  printf(std::string && s) : str(s) {}
  printf(const char *fmt, ...) {
    std::va_list va;
    va_start(va, fmt);
    this->str = wax::vsprintf(fmt, va);
    va_end(va);
  }
  operator std::string  () const { return str;         }
  operator const char * () const { return str.c_str(); }
 private:
  std::string str;
};
} // namespace types

//! @struct format
// @brief When you have an ostream, but printf(3) is life.
//
// I/O manipulator for sending traditionally-formatted output to std::ostream.
//
//     std::ofstream f("foo.txt");
//     f << wax::format("Answer to %s: %d", "life", 42) << std::endl;
//
struct format
{
  format(const char * const fmt, ...)
  {
    std::va_list args;
    va_start(args, fmt);
    s = wax::vsprintf(fmt, args);
    va_end(args);
  }

  std::ostream & operator () (std::ostream & os) const
  {
    os << s;
    return os;
  }

 private:
  std::string s;
};
}

static inline std::ostream & operator << (std::ostream &os, wax::format && f) { return f(os); }
