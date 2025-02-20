#pragma once

// In some versions of the standard library regular expressions are broken.
// When this occurs, use Boost regular expressions.  Use rgx:: as the scope, and
// it will do the right thing.

#if 1
// #ifdef _LIBCPP_VERSION
#   include <regex>
    namespace rgx = std;
#else
#   include <boost/regex.hpp>
    namespace rgx = boost;
#endif
