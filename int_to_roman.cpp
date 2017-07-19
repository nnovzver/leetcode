// Integer to Roman

// Given an integer, convert it to a roman numeral.
// Input is guaranteed to be within the range from 1 to 3999.
// I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000

#include <string>
#include <vector>
#include "catch.hpp"

using std::string;

class Solution
{
  struct IntRomanPair
  {
    int integer;
    char roman;
  };
  static const std::vector<IntRomanPair> romans;

public:
  string intToRoman(int num)
  {
    string res;

    for (auto i = romans.begin()+2; i < romans.end(); i += 2) {
      int div = num % 10;
      if (div == 4) {
        res.insert(0, string(1, (i-2)->roman) + string(1, (i-1)->roman));
      }
      else if (div == 9) {
        res.insert(0, string(1, (i-2)->roman) + string(1, i->roman));
      }
      else if (0 < div and div < 4) {
        res.insert(0, div, (i-2)->roman);
      }
      else if (div > 4) {
        res.insert(0, string(1, (i-1)->roman) + string(div-5, (i-2)->roman));
      }
      num /= 10;
      if (num == 0) break;
    }
    res.insert(0, string(num, 'M'));

    return res;
  }
};

const std::vector<Solution::IntRomanPair> Solution::romans = {
  {1, 'I'}, {5, 'V'}, {10, 'X'}, {50, 'L'}, {100, 'C'}, {500, 'D'}, {1000, 'M'}};

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
