#include "gtest/gtest.h"

#include <fstream>
#include <map>

#include "../src/str/dict"
#include "../src/str/impl/hash.hpp"

class hash_tests : public ::testing::Test
{
 public:
  wax::__hash::C14 hash_c14;
  wax::__hash::minimal hash_minimal;

  void read_dictionary(std::map<std::string, std::size_t> &map)
  {
    wax::csvec paths = {
      "/usr/share/dict/american-english"
    };

    for (const auto p : paths) {
      std::string word;
      std::ifstream s(p);
      if (!s.is_open())
        continue;

      int counter = 0;
      while (std::getline(s, word)) {
        // So it turns out that the hash algorithm mistakes apostrophes for a
        // lot of other letters.
        if (word.find_first_of('\'') != std::string::npos)
          continue;
        // The test takes several minutes if we include every word.
        if (++counter % 4)
          continue;
          map.emplace(word, 0);
      }
      s.close();
      break;
    }
  }

};

TEST_F(hash_tests, init)
{
  SUCCEED();
}

// Disabled by default since it takes many seconds to run.
TEST_F(hash_tests, DISABLED_basic_c14)
{
  // Load the English dictionary.
  std::map<std::string, std::size_t> dictionary;
  read_dictionary(dictionary);

  // Hash all the words;
  for (auto & item : dictionary)
    item.second = hash_c14(item.first.c_str());

  // See if there are any duplicates.
  for (auto i : dictionary) {
    for (auto j : dictionary) {
      if (i.first != j.first)
        ASSERT_FALSE(i.second == j.second);
    }
  }
}

TEST_F(hash_tests, minimal)
{
  ASSERT_EQ(hash_minimal("aa"), hash_minimal("ab"));
  ASSERT_NE(hash_minimal("aa"), hash_minimal("ba"));
}
