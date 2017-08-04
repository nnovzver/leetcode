// Implement strStr()

// Returns the index of the first occurrence of needle in haystack,
// or -1 if needle is not part of haystack.

#include <string>
#include "catch.hpp"

using std::string;

class Solution
{
public:
  int strStr(string haystack, string needle)
  {
    auto n = haystack.find(needle);
    return n != string::npos ? n : -1;
  }
};

TEST_CASE("strStr works properly")
{
  Solution sol;

  REQUIRE(0 == sol.strStr("", ""));
  REQUIRE(0 == sol.strStr("aba", "a"));
  REQUIRE(1 == sol.strStr("aba", "ba"));
  REQUIRE(-1 == sol.strStr("aba", "bar"));
}
