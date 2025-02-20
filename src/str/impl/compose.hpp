#pragma once

#include <chrono>
#include <string>

//! @file Functions for composing strings

namespace wax {
namespace str {

//! @brief join strings with a separator
//
// @param sep Separator string or character
// @param vals Iterable list of values to show
// @return String consisting of values separated by the separator.
//
template <class separator_type, class forward_iterable_type>
static inline std::string
join(const separator_type sep, const forward_iterable_type &vals)
{
  std::string result;
  for (auto v: vals) {
    if (result.size())
      result += sep;
    result += v;
  }
  return result;
}

namespace {

// Functions that work like std::localtime().
using time_flayer = struct tm * (*) (const ::time_t *);

//  Most time-stamping tasks are simple parameterizations of std::strfime(). The
//  following does the work by applying the zonificator to the given time_t, and
//  formatting the resulting structure as requested. The individual functions
//  that follow provide the parameters in each case.
//
// @todo For fun, rewrite this as the minimal template.
//
static inline
const std::string frob_time(
  const ::time_t when,
  const char * const fmt,
  time_flayer const zonificator)
{
  /*! @todo Can't use std::put_time because libstdc++ doesn't yet support it. */

  // --- begin lame ---
  char mbstr[48];
  std::strftime(mbstr, sizeof(mbstr), fmt, zonificator(&when));
  // --- end lame ---

  return std::string(mbstr);
}
} // anonymous namespace
} // namespace str


//! @brief Time stamp suitable to use as a file name.
//
// @param when (optional) Time to use; default is now.
// @return Local-time stamp formatted as "yyyy-mm-dd_HHhMMmSSs"
//
static inline
const std::string fntime(const ::time_t when = ::time(nullptr))
{
  //! @todo Windows localtime() handles DST differently and possibly wrongly and
  //! is thereby an hour off.
  //
  return str::frob_time(when, "%F_%Hh%Mm%Ss", std::localtime);
}


//! @brief ISO-8601-ish time stamp in UTC
//
// @param when (optional Time to use; default is now.
// @return UTC-time stamp formatted as "yyyy-mm-dd hh:mm:ss"
//
// @note This does not conform to IS0-8601 for UTC time coordinates. This is
// slightly more simplistic.
//
static inline
const std::string utime(const ::time_t when = ::time(nullptr))
{
  return str::frob_time(when, "%F %T", std::gmtime);
}


//! @brief sort of like ctime(3), but without the annoying extraneous newline
//
// @param when (optional) Time to use; default is now.
// @return Local-time stamp formatted as "yyyy-mm-dd hh:mm:ss"
//
static inline
const std::string ltime(const ::time_t when = ::time(nullptr))
{
  //! @todo Windows localtime() handles DST differently and possibly wrongly and
  //! is thereby an hour off.
  //
  return str::frob_time( when, "%F %T", std::localtime );
}
} // namespace wax
