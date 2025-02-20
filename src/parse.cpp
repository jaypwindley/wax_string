#include "./str/parse"
#include "./str/impl/fix_regex.hpp"


wax::svec wax::str::split(const std::string &s, const std::string &regex) {

  rgx::regex re(regex, rgx::regex::extended);

  // This is some magic in the regex iterator constructors.  If -1 is passed as
  // the submatch value, the construct below turns first and last into the
  // iterators delineating the entire sequence of what is NOT matched by the
  // regex.
  rgx::sregex_token_iterator first { s.begin(), s.end(), re, -1 };
  rgx::sregex_token_iterator last;

  auto strings = wax::svec { first, last };

  // Ignore a leading delimiters.
  if (!strings.empty()) {
    if (strings[0].empty())
      strings.erase(strings.begin());
  }

  return strings;
}


wax::svec wax::str::split(const std::string &s, const char delim)
{
  wax::svec strings;
  const char delim_str[2] { delim, '\0' };

  // Ignore a leading delimiter.
  auto last = s.find_first_not_of( delim_str, 0 );
  auto pos = s.find_first_of( delim_str, last );

  // Hopscotch down the string.
  while (pos != std::string::npos || last != std::string::npos) {
    strings.emplace_back(s.substr(last, pos - last));
    last = s.find_first_not_of(delim_str, pos);
    pos = s.find_first_of(delim_str, last);
  }

  return strings;
}
