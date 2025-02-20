#include <algorithm>
#include <functional>

#include "./str/edit"

// If delimiter is not defaulted, set the find_if predicate to be one that
// matches on everything but the delimeter, otherwise match on everything but
// whitespace.
//
#define ASSIGN_COMPARATOR(_delim_, _comp_)                              \
  if (_delim_)                                                          \
    _comp_ = [_delim_](int ch) -> int { return ch != _delim_; };        \
  else                                                                  \
    _comp_ = [](int ch) -> int { return ! std::isspace(ch); };          \


std::string &
wax::str::ltrim(std::string &s, const int delim)
{
  std::function<int(int)> comparator;
  ASSIGN_COMPARATOR(delim, comparator);
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), comparator));
  return s;
}


std::string &
wax::str::rtrim(std::string &s, const int delim)
{
  std::function<int(int)> comparator;
  ASSIGN_COMPARATOR(delim, comparator);
  s.erase(std::find_if(s.rbegin(), s.rend(), comparator ).base(), s.end());
  return s;
}

#undef ASSIGN_COMPARATOR

std::string &
wax::str::replace(std::string &s, const std::string &find, const std::string &repl)
{
  std::string::size_type pos = 0;
  while (!find.empty() && (pos = s.find(find, pos)) != std::string::npos) {
    s.replace(pos, find.size(), repl);
    pos += repl.size();
  }
  return s;
}
