#include <cstdio>
#include <memory>

#include "./str/format"

std::string
wax::vsprintf(const char *fmt, std::va_list valist)
{
  std::size_t              bufsize = 256;
  std::unique_ptr<char []> sp;
  std::string              s;

  int tries = 2;
  while (tries > 0) {
    sp.reset(new char [bufsize]);

    std::va_list valist2;
    va_copy(valist2, valist);
    auto ret = ::vsnprintf(sp.get(), bufsize, fmt, valist2);
    va_end(valist2);

    // If it didn't work; go around again and allocate bigger
    // buffer. ::vsnprintf(3) told us how many characters it would need,
    // excluding the terminating NUL, so this doesn't have to be an iterative
    // cycle.
    if (ret >= (int) bufsize) {
      bufsize = ret + 1;
      --tries;
    }
    else {
      s = sp.get();
      break;
    }
  }

  return s;
}
