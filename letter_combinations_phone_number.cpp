// Letter Combinations of a Phone Number
//
// Given a digit string, return all possible combinations that the number could
// represent.
//
// A mapping of digit to letters (just like on the telephone buttons) is given below:
// 0 -> ""
// 1 -> ""
// 2 -> "abc"
// 3 -> "def"
// 4 -> "ghi"
// 5 -> "jkl"
// 6 -> "mno"
// 7 -> "pqrs"
// 8 -> "tuv"
// 9 -> "wxyz"

#include <vector>
#include <string>
#include <array>
#include "catch.hpp"

using std::vector;
using std::string;

class Solution
{
private:
  const std::array<string, 10> digit_to_symbols{"", "", "abc", "def", "ghi", "jkl",
                                                "mno", "pqrs", "tuv", "wxyz"};
public:
  vector<string> letterCombinations(string digits)
  {
    if (digits.empty()) return {};

    vector<string> res;

    res.emplace_back("");

    for (size_t charIdx = 0; charIdx != digits.size(); ++charIdx) {
      auto d = digits[charIdx] - '0';
      if (d == 0 || d == 1) continue;
      if (d < 0 || 9 < d) return {};
      string const& combination = digit_to_symbols[d];

      vector<string> temp;
      for (size_t resIdx = 0; resIdx != res.size(); ++resIdx) {
        for (size_t charIdx = 0; charIdx != combination.size(); ++charIdx) {
          temp.emplace_back(res[resIdx] + combination[charIdx]);
        }
      }
      temp.swap(res);
    }

    return res == vector<string>{""} ? vector<string>{} : res;
  }
};

TEST_CASE("letterCombinations work properly", "[letterCombinations]")
{
  Solution sol;

  REQUIRE((vector<string>{})
          ==
          sol.letterCombinations("1b")
         );
  REQUIRE((vector<string>{})
          ==
          sol.letterCombinations("")
         );
  REQUIRE((vector<string>{})
          ==
          sol.letterCombinations("01")
         );
  REQUIRE((vector<string>{"a", "b", "c"})
          ==
          sol.letterCombinations("012")
         );
  REQUIRE((vector<string>{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"})
          ==
          sol.letterCombinations("23")
         );
  REQUIRE((vector<string>{"pt", "pu", "pv",
                          "qt", "qu", "qv",
                          "rt", "ru", "rv",
                          "st", "su", "sv"})
          ==
          sol.letterCombinations("78")
         );
}
