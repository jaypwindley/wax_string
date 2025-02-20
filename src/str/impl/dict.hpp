#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

//! @file Types useful for string-keyed and/or string-valued tables.

namespace wax {

//! @brief Map template using C-string keys.
//
// @tparam value_type The type of the value side of the map.
// @tparam comparator_type the comparator, by default wax::cstr::less.
//
// Efficient map when the keys are ordinary (but persistent) C strings,
// especially if they are string literals.  Compared to a std::string key_type,
// building lookup tables on this type will result in construction up to 5 times
// faster and lookups that are 4-10 times faster.
//
// @example
//
//    wax::cmap<char> ipa {
//        { "alpha", 'A' },
//        { "bravo", 'B' }.
//        { "charlie", 'C' }
//        // ...
//    };
//
// Caveat: the instantiator is responsible for ensuring the persistence of
// pointed-to strings. This is a fast implementation; not a safe one.  Use
// special caution when calling std::string::c_str() to decay a standard string
// to a C-string.  If the string is modified dynamically its internal storage
// may be reallocated and the value returned formerly by c_str() may no longer
// be valid.  Decay a std::string in this way only when its value will not be
// modified.
//
template <typename value_type, typename comparator_type = wax::__cstr::less>
using cmap = std::map< const char * const, value_type, comparator_type >;


//! @brief Unordered map template using C-string keys.
//
// @tparam value_type The type of the value side of the map
// @tparam hash The hashing algorithm.
//
// Similar to cmap above, only based on hashes instead of red-black trees.  Use
// this when it's not important to iterate over the map elements in a repeatable
// order, and search speed is paramount (such as for most largish look-up
// tables).
//
// Hashers are found in hash.h.  For small populations (N<50) stick with the
// default hasher, as it performs with very minimal overhead.  For larger
// populations or maps where the keys have a lot of identical prefixes, use
// wax::cstr::hash::C14, which is the full-blown hash function borrowed from
// the C++14 standard library.  The minimal hash becomes heinously
// non-performant where N > 50 (i.e., up to three orders of magnitude slower).
//
template <typename value_type, typename hash = wax::__hash::minimal>
using ucmap = std::unordered_map <
  const char * const,
  value_type,
  hash,
  wax::__cstr::equal >;


//! @section
//
// Here follows a bunch of convenience aliases for different types of containers
// for strings and string-to-string maps.

//! @typedef csvec
//! @typedef svec
//
// Vectors of strings, for convenience.
using csvec  = std::vector<const char *>;
using svec   = std::vector<std::string>;

//! @typedef sdict
//! @typedef csdict
//! @typedef ccdict
//
// Dictionaries (i.e., string-to-string mappings).
//
// Sdict is a std::string-to-std::string mapping, which mimics how lots of code
// commonly writes a dictionary when speed-optimization is not yet a concern.
// You would use this where the persistence of both the keys and the values
// cannot be ascertained in the design.
//
// Csdict uses C strings (ideally string literals) for keys and std::string for
// values.  It's best when the keys remain as literals (or well-behaved char *)
// but the values may change and be reassigned during the lifetime of the
// object, such that memory ownership is unclear and the automatic management of
// memory is required.
//
// Ccdict uses C strings (again, ideally string literals) for both keys and
// values, suggesting a mapping of constant strings to constant strings (e.g.,
// field names to the regular expression that parses their values).  If either
// the key or value is not a literal, it is presumed that the dictionary does
// not own the memory and that the strings are guaranteed by other means to
// persist for the lifetime of the dictionary.
//
using sdict   = std::map<const std::string, std::string>;
using csdict  = ucmap<std::string>;
using ccdict  = ucmap<const char *>;

} // namespace wax
