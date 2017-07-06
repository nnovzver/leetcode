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

#include <bits/stdc++.h>
#include "catch.hpp"

using std::vector;
using std::string;

class Solution
{
private:
  const std::array<string, 10> digit_to_symbols{"", "", "abc", "def", "ghi", "jkl",
                                                "mno", "pqrs", "tuv", "wxyz"};

  vector<string> buildResultFromCombinations(vector<string> const& combinations)
  {
    if (combinations.size() == 0) return {};

    size_t res_size = 1;
    for (string const& s : combinations) {
      res_size *= s.size();
    }

    vector<string> res;
    res.reserve(res_size);

    string temp(combinations.size(), ' ');
    buildResultFromCombinationsIter(combinations, 0, temp, res);

    return res;
  }

  void buildResultFromCombinationsIter(vector<string> const& combinations,
                                   size_t layer, string& cur, vector<string>& res)
  {
    if (layer >= combinations.size()) {
      res.emplace_back(cur);
      return;
    }

    //iteration from left to right node on layer
    for (size_t i = 0; i < combinations[layer].size(); ++i) {
      cur[layer] = combinations[layer][i];
      buildResultFromCombinationsIter(combinations, layer + 1, cur, res);
    }
  }

public:
  vector<string> letterCombinations(string digits)
  {
    vector<string> combinations;
    combinations.reserve(digits.size());

    for (auto di = digits.begin(); di != digits.end(); ++di) {
      int d = *di - '0';
      if (d < 2) continue;
      combinations.emplace_back(digit_to_symbols[d]);
    }

    return buildResultFromCombinations(combinations);
  }
};

TEST_CASE("letterCombinations work properly", "[letterCombinations]")
{
  Solution sol;

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