// Divide Two Integers

// Divide two integers without using multiplication, division and mod operator.

// If it is overflow, return INT_MAX.

#include <climits>
#include "catch.hpp"

class Solution
{
public:
  int divide(int dividend, int divisor)
  {
    if (divisor == 0) return INT_MAX;
    if (dividend > 0 and divisor < 0) {
      return -divide(dividend, -divisor);
    }
    else if (dividend < 0 and divisor > 0) {
      return -divide(-dividend, divisor);
    }
    else if (dividend < 0 and divisor < 0) {
      return divide(-dividend, -divisor);
    }

    int quotient = 0;
    while (dividend >= divisor) {
      dividend -= divisor;
      ++quotient;
    }

    return quotient;
  }
};

TEST_CASE("divide works properly")
{
  Solution sol;

  REQUIRE(INT_MAX == sol.divide(10, 0));
  REQUIRE(2 == sol.divide(10, 5));
  REQUIRE(1 == sol.divide(9, 5));
  REQUIRE(0 == sol.divide(4, 5));
  REQUIRE(-2 == sol.divide(10, -5));
  REQUIRE(-2 == sol.divide(-10, 5));
  REQUIRE(2 == sol.divide(-10, -5));
}
