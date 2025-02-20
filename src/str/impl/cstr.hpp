#pragma once

#include <cstring>

namespace wax {
namespace __cstr {

//! @brief implementation of std::less for C strings, for use in ordered maps.
struct less   /* : public std::less */
{
  bool operator() (const char * const k1, const char * const k2) const {
    return std::strcmp(k1, k2) < 0;
  }
};

//! @brief implementation of std::equal_t for C strings.
struct equal   /* : public std::equal_to<const char * const> */
{
  bool operator() (const char * const k1, const char * const k2) const {
    return std::strcmp(k1, k2) == 0;
  }
};

} // namespace __cstr
} // namespace wax
