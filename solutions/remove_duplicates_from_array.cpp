// Remove Duplicates from Sorted Array

// Given a sorted array, remove the duplicates in place such that
// each element appear only once and return the new length.

// Do not allocate extra space for another array, you must do this in place with constant memory.

// For example,
// Given input array nums = [1,1,2],

// Your function should return length = 2, with the first two elements
// of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.

#include <vector>
#include <algorithm>
#include "catch.hpp"

using std::vector;

class Solution
{
public:
  int removeDuplicates(vector<int>& nums)
  {
    return std::unique(nums.begin(), nums.end()) - nums.begin();
  }
};

class AlternativeSolution
{
public:
  int removeDuplicates(vector<int>& nums)
  {
    auto i = nums.begin();

    while (i != nums.end()) {
      auto uniq = std::find_if_not(i, nums.end(), [&](int val){return val == *i;});
      size_t dist = std::distance(i, uniq);
      if (dist != 1) {
        nums.erase(std::next(i), uniq);
      }
      i = std::next(i);
    }
    return std::distance(nums.begin(), nums.end());
  }
};

TEST_CASE("removeDuplicates works properly")
{
  Solution sol;
  AlternativeSolution altsol;

  {
    vector<int> v;
    REQUIRE(0 == sol.removeDuplicates(v));
  }
  {
    vector<int> v = {1};
    REQUIRE(1 == sol.removeDuplicates(v));
  }
  {
    vector<int> v = {1, 2, 2};
    REQUIRE(2 == sol.removeDuplicates(v));
  }
  {
    vector<int> v = {1, 1, 2, 2, 3, 3, 3};
    REQUIRE(3 == sol.removeDuplicates(v));
  }

  // alternative
  {
    vector<int> v;
    REQUIRE(0 == altsol.removeDuplicates(v));
  }
  {
    vector<int> v = {1};
    REQUIRE(1 == altsol.removeDuplicates(v));
  }
  {
    vector<int> v = {1, 2, 2};
    REQUIRE(2 == altsol.removeDuplicates(v));
  }
  {
    vector<int> v = {1, 1, 2, 2, 3, 3, 3};
    REQUIRE(3 == altsol.removeDuplicates(v));
  }
}

#ifdef SELFBENCH
#include "benchmark/benchmark.h"
static void BM_removeDuplicates(benchmark::State& state) {
  Solution sol;
  vector<int> v = {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3};

  while (state.KeepRunning()) {
    int res = sol.removeDuplicates(v);
    benchmark::DoNotOptimize(res);
  }
}
BENCHMARK(BM_removeDuplicates);

static void BM_removeDuplicates_alt(benchmark::State& state) {
  AlternativeSolution sol;
  vector<int> v = {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3};

  while (state.KeepRunning()) {
    int res = sol.removeDuplicates(v);
    benchmark::DoNotOptimize(res);
  }
}
BENCHMARK(BM_removeDuplicates_alt);
#endif // SELFBENCH
