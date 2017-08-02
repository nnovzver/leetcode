// Remove Element

// Given an array and a value, remove all instances of that
// value in place and return the new length.

// Do not allocate extra space for another array, you must
// do this in place with constant memory.

// The order of elements can be changed. It doesn't matter
// what you leave beyond the new length.

// Example:
// Given input array nums = [3,2,2,3], val = 3

// Your function should return length = 2, with the first two elements of nums being 2.

#include <vector>
#include <algorithm>
#include "catch.hpp"

using std::vector;

class Solution
{
public:
  int removeElement(vector<int>& nums, int val)
  {
    return std::remove(nums.begin(), nums.end(), val) - nums.begin();
  }
};

TEST_CASE("removeElement works properly")
{
  Solution sol;

  {
    vector<int> vec;
    REQUIRE(0 == sol.removeElement(vec, 3));
  }

  {
    vector<int> vec = {1, 2, 3, 3, 4};
    REQUIRE(3 == sol.removeElement(vec, 3));
    REQUIRE(1 == vec[0]);
    REQUIRE(2 == vec[1]);
    REQUIRE(4 == vec[2]);
  }
}
