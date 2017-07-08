// 4Sum

// Given an array S of n integers, are there elements a, b, c, and d in S
// such that a + b + c + d = target? Find all unique quadruplets in the
// array which gives the sum of target.

// Note: The solution set must not contain duplicate quadruplets.

// For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.
//
// A solution set is:
// [
//   [-1,  0, 0, 1],
//   [-2, -1, 1, 2],
//   [-2,  0, 0, 2]
// ]

#include <vector>
#include <algorithm>
#include "catch.hpp"

using std::vector;

class Solution
{
public:
  vector<vector<int>> fourSum(vector<int>& nums, int target)
  {
    if (nums.size() < 4) return {};
    vector<vector<int>> res;

    std::sort(nums.begin(), nums.end());

    for (auto first = nums.begin(); first < nums.end()-3;) {
      for (auto second = first+1; second < nums.end()-2;) {
        auto third = second+1;
        auto fourth = nums.end()-1;

        int new_target = target - *first - *second;
        while (third < fourth) {
          int diff = new_target - *third - *fourth;
          if (diff < 0) {
            while (--fourth != third and *fourth == *(fourth+1));
          }
          else if (diff > 0) {
            while (++third != fourth and *third == *(third-1));
          }
          else {
            res.emplace_back(vector<int>{*first, *second, *third, *fourth});
            while (++third != fourth and *third == *(third-1));
            while (--fourth != third and *fourth == *(fourth+1));
          }
        }
        while (++second < nums.end()-2 and *second == *(second-1));
      }
      while (++first < nums.end()-3 and *first == *(first-1));
    }

    return res;
  }
};

TEST_CASE("fourSum work properly", "[fourSum]")
{
  Solution sol;

  vector<int> v1 = {1, 0, -1, 0, -2, 2};
  vector<int> v2 = {1, 2, 3};

  REQUIRE(vector<vector<int>>{} == sol.fourSum(v2, 0));
  REQUIRE((vector<vector<int>>{
      {-2, -1, 1, 2},
      {-2, 0, 0, 2},
      {-1, 0, 0, 1},
  }) == sol.fourSum(v1, 0));
}
