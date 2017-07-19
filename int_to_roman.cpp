// Integer to Roman

// Given an integer, convert it to a roman numeral.
// Input is guaranteed to be within the range from 1 to 3999.
// I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000

#include <string>
#include <array>
#include <algorithm>
#include "catch.hpp"

using std::string;

class Solution
{
  static const std::array<char, 7> romans;

public:
  string intToRoman(int num)
  {
    string res;
    res.reserve(10);

    for (size_t i = 2; i < romans.size(); i += 2) {
      int div = num % 10;
      if (div == 4) {
        res.append(1, romans[i-1]);
        res.append(1, romans[i-2]);
      }
      else if (div == 9) {
        res.append(1, romans[i]);
        res.append(1, romans[i-2]);
      }
      else if (0 < div and div < 4) {
        res.append(div, romans[i-2]);
      }
      else if (div > 4) {
        res.append(div-5, romans[i-2]);
        res.append(1, romans[i-1]);
      }
      num *= 0.1;
      if (num == 0) break;
    }
    res.append(num, 'M');

    std::reverse(res.begin(), res.end());

    return res;
  }
};

const std::array<char, 7> Solution::romans = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

TEST_CASE("intToRoman works properly", "[intToRoman]")
{
  Solution sol;

  REQUIRE("I" == sol.intToRoman(1));
  REQUIRE("III" == sol.intToRoman(3));
  REQUIRE("IV" == sol.intToRoman(4));
  REQUIRE("V" == sol.intToRoman(5));
  REQUIRE("VIII" == sol.intToRoman(8));
  REQUIRE("X" == sol.intToRoman(10));
  REQUIRE("XII" == sol.intToRoman(12));
  REQUIRE("XIV" == sol.intToRoman(14));
  REQUIRE("XV" == sol.intToRoman(15));
  REQUIRE("L" == sol.intToRoman(50));
  REQUIRE("XC" == sol.intToRoman(90));
  REQUIRE("MCL" == sol.intToRoman(1150));
  REQUIRE("CM" == sol.intToRoman(900));
  REQUIRE("MCMLIV" == sol.intToRoman(1954));
  REQUIRE("MCMXC" == sol.intToRoman(1990));
  REQUIRE("MMXIV" == sol.intToRoman(2014));
}
