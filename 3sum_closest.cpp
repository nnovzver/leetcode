#include <cassert>
#include <vector>

using std::vector;

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

class Solution {
public:
  template <typename ForwardIt, class T>
  ForwardIt closest_search(ForwardIt first, ForwardIt last, T const &value) {
    assert(first < last);
    auto i = std::lower_bound(first, last, value);
    if (i == last) {
      return last - 1;
    } else if (i == first) {
      return first;
    } else {
      if (std::abs(value - *i) <= std::abs(value - *(i - 1))) {
        return i;
      } else {
        return i - 1;
      }
    }
  }

  int threeSumClosest(vector<int> &nums, int target) {
    assert(nums.size() >= 3);

    std::sort(nums.begin(), nums.end());
    auto first = nums.begin(), second = first + 1, third = nums.end() - 1;

    int closest_sum = *first + *second + *third;
    while (std::distance(first, third) >= 2) {
      int first_plus_third = *first + *third;
      int second_target = target - first_plus_third;
      second = closest_search(first + 1, third, second_target);
      int cur_sum = first_plus_third + *second;
      // find closest sum
      if (std::abs(target - closest_sum) > std::abs(target - cur_sum)) {
        closest_sum = cur_sum;
      }
      // check if target sum found
      if (closest_sum == target) {
        return closest_sum;
      }

      if (std::distance(first, second) <= std::distance(second, third)) {
        --third;
      }
      else {
        ++first;
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

  SECTION("check brute force solution") {
    REQUIRE(0 == sol.threeSumClosestBruteForce(v1, 0));
    REQUIRE(3 == sol.threeSumClosestBruteForce(v2, 3));
  }

  SECTION("check fast solution") {
    REQUIRE(0 == sol.threeSumClosest(v1, 0));
    REQUIRE(3 == sol.threeSumClosest(v2, 3));
  }
}
