// Generate Parentheses

// Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
// For example, given n = 3, a solution set is:

// [
// "((()))",
// "(()())",
// "(())()",
// "()(())",
// "()()()"
// ]

#include <string>
#include <vector>
#include <stack>
#include <unordered_set>
#include "catch.hpp"

using std::string;
using std::vector;

class Solution
{
public:
  vector<string> generateParenthesis(int n)
  {
    if (n == 0) return vector<string>{};

    std::stack<string> stack;
    std::unordered_set<string> set;

    stack.push(string(n, '(') + string(n, ')'));
    set.emplace(stack.top());

    while (not stack.empty()) {
      string s = stack.top(); stack.pop();

      int inside = 0;
      for (size_t i = 0; i != s.size(); ++i) {
        if (s[i] == '(') {
          ++inside;
        }
        else {
          --inside;
          if (inside) {
            string copy = s;
            std::swap(copy[i], copy[i-1]);
            if (set.emplace(copy).second) {
              stack.push(copy);
            }
          }
        }
      }
    }

    return vector<string>(set.begin(), set.end());
  }
};

TEST_CASE("generateParenthesis works properly", "[generateParenthesis]")
{
  Solution sol;

  REQUIRE(vector<string>{} == sol.generateParenthesis(0));
  REQUIRE(vector<string>{"()"} == sol.generateParenthesis(1));

  vector<string> res;
  std::unordered_set<string> orig;

  res = sol.generateParenthesis(2);
  orig = {"(())", "()()"};
  for (auto& s : res) {
    REQUIRE(orig.count(s));
    orig.erase(s);
  }
  REQUIRE(orig.empty());


  res = sol.generateParenthesis(3);
  orig = {"((()))", "()()()", "(())()", "()(())", "(()())"};
  for (auto& s : res) {
    REQUIRE(orig.count(s));
    orig.erase(s);
  }
  REQUIRE(orig.empty());
}
