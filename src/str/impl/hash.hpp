#pragma once

namespace wax {
namespace __hash {

//! @brief The sooper-dooper hash algorithm from C++14.
//* @todo Deprecate this in favor of C++17
struct C14   /* : public std::hash<const char * const> */
{
 private:
  void integrate(size_t &hash, const char p) const {
    hash ^= p + 0x9e3779b9 + (hash << 6) + (hash >> 2);
  }

 public:
  std::size_t operator() (const char * p) const {
    size_t hash { 0 };
    while (*p)
      integrate(hash, *p++);
    return hash;
  }
};

//! As close as we'll get to the minimal perfect hash for short alphabetic
//! strings, suitable for small-to-mediumly populated maps.  The underlying
//! rationale is that the complexity saved in the key computation may apply to
//! walking the hash chain.
struct minimal  /* : public std::hash<const char * const> */
{
  std::size_t operator() (const char * const p) const {
    if (*p < 'a' || *p > 'z') {
      if (*p < 'A' || *p > 'Z')
        return 0;
      else
        return *p - 'A';
    }
    else
      return *p - 'a';
  }
};

} // namespace __hash
} // namespace wax
