// Next Permutation

// Implement next permutation, which rearranges numbers into
// the lexicographically next greater permutation of numbers.

// If such arrangement is not possible, it must rearrange it
// as the lowest possible order (ie, sorted in ascending order).

// The replacement must be in-place, do not allocate extra memory.

// Here are some examples. Inputs are in the left-hand column
// and its corresponding outputs are in the right-hand column.
// 1,2,3 → 1,3,2
// 3,2,1 → 1,2,3
// 1,1,5 → 1,5,1

#include <vector>
#include <algorithm>
#include "catch.hpp"

using std::vector;

class Solution
{
public:
    void nextPermutation(vector<int>& nums)
    {
      std::next_permutation(nums.begin(), nums.end());
    }
};

TEST_CASE("nextPermutation works properly")
{
  Solution sol;
  {
    vector<int> vec = {1, 2, 3};
    sol.nextPermutation(vec);
    REQUIRE(vec == vector<int>({1, 3, 2}));
    sol.nextPermutation(vec);
    REQUIRE(vec == vector<int>({2, 1, 3}));
    sol.nextPermutation(vec);
    REQUIRE(vec == vector<int>({2, 3, 1}));
    sol.nextPermutation(vec);
    REQUIRE(vec == vector<int>({3, 1, 2}));
    sol.nextPermutation(vec);
    REQUIRE(vec == vector<int>({3, 2, 1}));
    sol.nextPermutation(vec);
    REQUIRE(vec == vector<int>({1, 2, 3}));
  }
}
