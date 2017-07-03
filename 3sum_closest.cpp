#include <cassert>
#include <vector>

using std::vector;

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

class Solution {
public:

  int threeSumClosest(vector<int> &nums, int target) {
    assert(nums.size() >= 3);

    std::sort(nums.begin(), nums.end());

    int closest_sum = *nums.begin() + *(nums.begin()+1) + *(nums.begin()+2);
    int closest_diff = std::abs(target - closest_sum);

    for (auto first = nums.begin(); first != nums.end()-2; ++first) {
      auto second = first+1;
      auto third = nums.end()-1;

      int target_out_first = target - *first;
      while (second < third) {
        int cur_sum = *third + *second;
        int cur_diff = std::abs(target_out_first - cur_sum);

        if (cur_diff < closest_diff) {
          closest_sum = cur_sum + *first;
          closest_diff = cur_diff;
        }

        if (closest_diff == 0) return target;

        if (cur_sum < target_out_first) {
          ++second;
        }
        else {
          --third;
        }
      }
    }
    return closest_sum;
  }

  int threeSumClosestBruteForce(vector<int> &nums, int target) {
    assert(nums.size() >= 3);

    std::sort(nums.begin(), nums.end());

    int closest_sum = *nums.begin() + *(nums.begin()+1) + *(nums.begin()+2);

    for (auto first = nums.begin(); first < nums.end()-2; ++first) {
      for (auto second = first+1; second < nums.end()-1; ++second) {
        for (auto third = second+1; third < nums.end(); ++third) {
          int cur_sum = *first + *second + *third;
          if (std::abs(target - cur_sum) < std::abs(target - closest_sum)) {
            closest_sum = cur_sum;
            //std::cout << *first << " " << *second << " " << *third << "\n";
          }
        }
      }
    }
    return closest_sum;
  }
};

TEST_CASE("threeSumClosest work properly", "[threeSumClosest]")
{
  Solution sol;
  std::vector<int> v1 = {-55, -24, -18, -11, -7, -3, 4, 5, 6, 9, 11, 23, 33};
  std::vector<int> v2 = {0, 0, 0, 0, 1, -1, 2, -2, 3, -3, 7, -7, 4, -4, 5, -5, 6, -6};
  std::vector<int> v3 = {0, 1, 2, 3};
  std::vector<int> v4 = {0, 1, 2};
  std::vector<int> v5 = {-10, -9, -1, 7, 10};
  std::vector<int> v6 = {-10, -7, 1, 9, 10};
  std::vector<int> v7 = {0, 0, 0, 1, 2, 3};
  std::vector<int> v8 = {-3, -2, -1, 0, 0, 0};

  SECTION("check brute force solution") {
    REQUIRE(0 == sol.threeSumClosestBruteForce(v1, 0));
    REQUIRE(3 == sol.threeSumClosestBruteForce(v2, 3));
  }

  SECTION("check fast solution") {
    REQUIRE(0 == sol.threeSumClosest(v1, 0));

    REQUIRE(3 == sol.threeSumClosest(v2, 3));

    REQUIRE(3 == sol.threeSumClosest(v3, 3));
    REQUIRE(3 == sol.threeSumClosest(v3, 2));
    REQUIRE(6 == sol.threeSumClosest(v3, 6));
    REQUIRE(6 == sol.threeSumClosest(v3, 7));

    REQUIRE(3 == sol.threeSumClosest(v4, 3));
    REQUIRE(3 == sol.threeSumClosest(v4, 10));
    REQUIRE(3 == sol.threeSumClosest(v4, -10));

    REQUIRE(0 == sol.threeSumClosest(v5, 0));

    REQUIRE(0 == sol.threeSumClosest(v6, 0));

    REQUIRE(0 == sol.threeSumClosest(v7, 0));
    REQUIRE(1 == sol.threeSumClosest(v7, 1));
    REQUIRE(2 == sol.threeSumClosest(v7, 2));
    REQUIRE(3 == sol.threeSumClosest(v7, 3));

    REQUIRE(0 == sol.threeSumClosest(v8, 0));
    REQUIRE(-1 == sol.threeSumClosest(v8, -1));
    REQUIRE(-2 == sol.threeSumClosest(v8, -2));
    REQUIRE(-3 == sol.threeSumClosest(v8, -3));
  }
}
