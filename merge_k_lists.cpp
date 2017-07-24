// Merge k Sorted Lists

// Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <vector>
#include <algorithm>
#include "list_node.h"
#include "catch.hpp"

using std::vector;

class Solution
{
public:
  ListNode* mergeKLists(vector<ListNode*>& lists)
  {
    ListNode* res = nullptr;
    ListNode* tail = nullptr;

    auto lists_begin = lists.begin();
    auto lists_end = std::partition(lists_begin, lists.end(),
      [](ListNode* v){return v != nullptr;});

    // if no lists in vector
    if (lists_end == lists_begin) return nullptr;

    // init res and tail
    auto min_head = std::min_element(lists_begin, lists_end,
      [](ListNode* first, ListNode* second){return first->val < second->val;});
    tail = res = *min_head;
    *min_head = (*min_head)->next;

    while (lists_begin != lists_end) {
      auto min_head = std::min_element(lists_begin, lists_end,
        [](ListNode* first, ListNode* second){return first->val < second->val;});
      tail->next = *min_head;
      tail = tail->next;
      *min_head = (*min_head)->next;

      lists_end = std::partition(lists_begin, lists_end,
        [](ListNode* v){return v != nullptr;});
      if (lists_end - lists_begin == 1) {
        tail->next = *lists_begin;
      }
    }

    return res;
  }
};

TEST_CASE("mergeKLists works properly", "[mergeKLists]")
{
  Solution sol;

  {
    vector<ListNode*> arg = {nullptr, nullptr, nullptr};
    REQUIRE(nullptr == sol.mergeKLists(arg));
  }

  {
    vector<ListNode*> arg = {create_list(1, 2, 3).release(), nullptr, nullptr};
    ListNode* ret = sol.mergeKLists(arg);
    auto res = create_list(1, 2, 3);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }

  {
    vector<ListNode*> arg = {
      create_list(1, 3, 5).release(),
      create_list(2, 4, 6).release(),
      nullptr};
    auto res = create_list(1, 2, 3, 4, 5, 6);

    ListNode* ret = sol.mergeKLists(arg);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }
  {
    vector<ListNode*> arg = {
      create_list(1, 4, 7).release(),
      create_list(2, 5, 8).release(),
      create_list(3, 6, 9).release()};
    auto res = create_list(1, 2, 3, 4, 5, 6, 7, 8, 9);

    ListNode* ret = sol.mergeKLists(arg);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }
}
