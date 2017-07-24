// Valid Parentheses

// Given a string containing just the characters
// '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
// The brackets must close in the correct order,
// "()" and "()[]{}" are all valid but "(]" and "([)]" are not."

#include <string>
#include <stack>
#include <map>
#include "catch.hpp"

using std::string;

class Solution
{
  static const std::map<char, char> parens;
public:
  bool isValid(string s)
  {
    std::stack<char> stack;
    for (size_t i = 0; i != s.size(); ++i) {
      char cur = s[i];

      switch (cur) {
      case '(':
      case '{':
      case '[':
        stack.push(cur);
        break;

      default:
        if (!stack.empty() and parens.at(cur) == stack.top()) {
          stack.pop();
        }
        else {
          return false;
        }
        break;
      }
    }
    return stack.empty();
  }
};

const std::map<char, char> Solution::parens = {{')', '('}, {']', '['}, {'}', '{'}};

TEST_CASE("valid_parentheses solution works properly", "[valid_parentheses]")
{
  Solution sol;

  REQUIRE(true == sol.isValid(""));
  REQUIRE(true == sol.isValid("()"));
  REQUIRE(true == sol.isValid("()[]{}"));
  REQUIRE(true == sol.isValid("(([{}]))"));
  REQUIRE(false == sol.isValid("(]"));
  REQUIRE(false == sol.isValid("([)]"));
}
