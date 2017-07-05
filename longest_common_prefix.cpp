#include <string>
#include <vector>
#include "catch.hpp"

using std::string;
using std::vector;

class Solution {
public:
  string longestCommonPrefix(vector<string> &strs) {
    if (strs.size() == 0)
      return "";

    std::string prefix = strs[0];
    size_t prefix_size = prefix.size();
    for (auto si = strs.begin() + 1; si != strs.end() and prefix_size > 0; ++si) {
      size_t i = 0;
      for (; i < std::min(prefix_size, si->size()) and prefix[i] == si->at(i); ++i)
        ;
      prefix_size = i;
    }
    return prefix.substr(0, prefix_size);
  }
};


TEST_CASE("longestCommonPrefix work properly", "[longestCommonPrefix]")
{
  Solution sol;
  vector<string> v1 = {"abcd", "abc", "ab"};
  vector<string> v2 = {"ab", "abc", "abcd"};

  REQUIRE("ab" == sol.longestCommonPrefix(v1));
  REQUIRE("ab" == sol.longestCommonPrefix(v2));
}
