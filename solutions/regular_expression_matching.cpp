#include <string>
#include <cassert>

#include "catch.hpp"

using std::string;

class Solution {
public:
  template <typename It>
  bool isMatchStar(char c, It const& sbeg, It const& send, It const& pbeg, It const& pend) {
    auto eatall = std::find_if_not(
        sbeg, send, [c](char val) { return val == c || c == '.'; });

    do {
      if (isMatchHere(eatall, send, pbeg, pend)) {
        return true;
      }
    } while (eatall-- != sbeg);
    return false;
  }

  template <typename It> bool isMatchHere(It const& sbeg, It const& send, It const& pbeg, It const& pend) {
    if (pbeg == pend) {
      if (sbeg == send) {
        return true;
      } else {
        return false;
      }
    }
    if ((pbeg + 1) != pend && *(pbeg + 1) == '*') {
      // '**' sequence of two stars is prohibited
      assert(pbeg + 2 == pend || *(pbeg + 2) != '*');
      return isMatchStar(*pbeg, sbeg, send, pbeg + 2, pend);
    }
    if (sbeg != send and (*pbeg == '.' || *pbeg == *sbeg)) {
      return isMatchHere(sbeg + 1, send, pbeg + 1, pend);
    }
    return false;
  }

  bool isMatch(string s, string p) {
    return isMatchHere(s.begin(), s.end(), p.begin(), p.end());
  }
};

TEST_CASE("isMatch work properly", "[isMatch]")
{
  Solution sol;

  REQUIRE(false == sol.isMatch("aa", "a"));
  REQUIRE(false == sol.isMatch("a", "aa"));
  REQUIRE(true == sol.isMatch("", ""));
  REQUIRE(false == sol.isMatch("", "a"));
  REQUIRE(false == sol.isMatch("a", ""));
  REQUIRE(true == sol.isMatch("a", "a"));
  REQUIRE(true == sol.isMatch("a", "."));
  REQUIRE(true == sol.isMatch("abc", "abc"));
  REQUIRE(true == sol.isMatch("abc", "a.c"));
  REQUIRE(false == sol.isMatch("abc", "ab"));
  REQUIRE(false == sol.isMatch("abc", "a"));
  REQUIRE(true == sol.isMatch("abc", "ab*c"));
  REQUIRE(true == sol.isMatch("abbbbbbc", "ab*c"));
  REQUIRE(true == sol.isMatch("ac", "ab*c"));
  REQUIRE(false == sol.isMatch("abc", "ab*"));
  REQUIRE(true == sol.isMatch("abc", "a.*c"));
  REQUIRE(false == sol.isMatch("abcc", "ab*c"));
  REQUIRE(true == sol.isMatch("abbbbbbbbbbbbbbbbbbcc", "ab*cc"));
  REQUIRE(true == sol.isMatch("abbbbbbbbbbbbbbbbbbccc", "a.*ccc"));
}
