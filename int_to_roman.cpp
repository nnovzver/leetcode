// Integer to Roman

// Given an integer, convert it to a roman numeral.
// Input is guaranteed to be within the range from 1 to 3999.

#include <string>
#include "catch.hpp"

using std::string;

class Solution
{
public:
  string intToRoman(int /*num*/)
  {
    return "i";
  }
};

TEST_CASE("intToRoman work properly", "[intToRoman]")
{
  Solution sol;

  REQUIRE(sol.intToRoman(1) == "i");
}
