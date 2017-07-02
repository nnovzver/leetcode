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
      } else if (cur_sum > target) {
        --third;
      } else {
        ++first;
      }
    }
    return closest_sum;
  }
};