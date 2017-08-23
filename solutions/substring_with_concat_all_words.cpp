// Substring with Concatenation of All Words

// You are given a string, s, and a list of words, words,
// that are all of the same length. Find all starting indices
// of substring(s) in s that is a concatenation of each word
// in words exactly once and without any intervening characters.

// For example, given:
// s: "barfoothefoobarman"
// words: ["foo", "bar"]

// You should return the indices: [0,9].
// (order does not matter).

#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include "catch.hpp"

using std::string;
using std::vector;

class Solution
{
public:
  vector<int> findSubstring(string s, vector<string>& words)
  {
    if (words.empty() or s.empty()) return {};

    std::sort(words.begin(), words.end());
    vector<int> res;
    string pattern;

    do {
      pattern = "";
      pattern = std::accumulate(words.begin(), words.end(), pattern);
      string::size_type pos = 0;

      for (int i = 0; i < 4; ++i) {
        pos = s.find(pattern, pos);
        if (pos != string::npos) {
          res.emplace_back(pos);
        }
        else {
          break;
        }
        ++pos;
      }
    } while (std::next_permutation(words.begin(), words.end()));

    return res;
  }
};

TEST_CASE("findSubstring works properly")
{
  Solution sol;

  vector<string> words = {"foo", "bar"};
  vector<int> expected = {0, 9};
  REQUIRE(expected == sol.findSubstring("barfoothefoobarman", words));

  REQUIRE(vector<int>{} == sol.findSubstring("", words));

  {
    vector<string> words = {};
    REQUIRE(vector<int>{} == sol.findSubstring("barfoothefoobarman", words));
  }
}
