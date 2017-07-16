// Roman to Integer

// Given a roman numeral, convert it to an integer.
// Input is guaranteed to be within the range from 1 to 3999.
// I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000
#include <string>
#include <map>
#include <locale>
#include "catch.hpp"

using std::string;

class Solution
{
  static const std::map<char, int> r2iMap;
public:
  int romanToInt(string s)
  {
    int number = 0;
    for (size_t i = 0; i != s.size(); ++i) {
      const char cur = std::tolower(s[i]);
      // cur is not last symbol
      if (i + 1 != s.size()) {
        const char next = std::tolower(s[i+1]);
        // is a substractive notation
        if (r2iMap.at(cur) < r2iMap.at(next)) {
          number += r2iMap.at(next) - r2iMap.at(cur);
          ++i;
          continue;
        }
      }
      number += r2iMap.at(cur);
    }
    return number;
  }
};

const std::map<char, int> Solution::r2iMap =
  {{'i', 1}, {'v', 5}, {'x', 10}, {'l', 50}, {'c', 100}, {'d', 500}, {'m', 1000}};

TEST_CASE("romanToInt work properly", "[romanToInt]")
{
  Solution sol;

  REQUIRE(1 == sol.romanToInt("i"));
  REQUIRE(1 == sol.romanToInt("I"));
  REQUIRE(4 == sol.romanToInt("iv"));
  REQUIRE(1954 == sol.romanToInt("MCMLIV"));
  REQUIRE(1990 == sol.romanToInt("mcmxc"));
  REQUIRE(2014 == sol.romanToInt("MMXIV"));
}
