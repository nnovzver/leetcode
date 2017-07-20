// Merge Two Sorted Lists

// Merge two sorted linked lists and return it as a new list.
// The new list should be made by splicing together the nodes of the first two lists.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include "list_node.h"
#include "catch.hpp"

class Solution
{
public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
  {
    if (!l1) return l2;
    else if (!l2) return l1;

    ListNode* tail = nullptr;
    ListNode* res = nullptr;

    ListNode** min_node = l1->val < l2->val ? &l1 : &l2;
    res = tail = *min_node;
    *min_node = (*min_node)->next;

    while (l1 and l2) {
      ListNode** min_node = l1->val < l2->val ? &l1 : &l2;
      tail->next = *min_node;
      tail = *min_node;
      *min_node = (*min_node)->next;
    }

    ListNode* last = l1 != nullptr ? l1 : l2;
    tail->next = last;

    return res;
  }
};

TEST_CASE("mergeTwoLists works properly", "[mergeTwoLists]")
{
  Solution sol;

  REQUIRE(nullptr == sol.mergeTwoLists(nullptr, nullptr));

  {
    ListNode* l1 = create_list(1).release();
    auto res = create_list(1);
    ListNode* ret = sol.mergeTwoLists(nullptr, l1);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }

  {
    ListNode* l1 = create_list(1).release();
    auto res = create_list(1);
    ListNode* ret = sol.mergeTwoLists(l1, nullptr);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }

  {
    ListNode* l1 = create_list(1).release();
    ListNode* l2 = create_list(2).release();
    auto res = create_list(1, 2);
    ListNode* ret = sol.mergeTwoLists(l1, l2);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }

  {
    ListNode* l1 = create_list(1, 2).release();
    ListNode* l2 = create_list(3).release();
    auto res = create_list(1, 2, 3);
    ListNode* ret = sol.mergeTwoLists(l1, l2);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }

  {
    ListNode* l1 = create_list(5, 6).release();
    ListNode* l2 = create_list(1, 2, 3, 4).release();
    auto res = create_list(1, 2, 3, 4, 5, 6);
    ListNode* ret = sol.mergeTwoLists(l1, l2);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }

  {
    ListNode* l1 = create_list(2, 6).release();
    ListNode* l2 = create_list(1, 2, 2, 4).release();
    auto res = create_list(1, 2, 2, 2, 4, 6);
    ListNode* ret = sol.mergeTwoLists(l1, l2);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }
}
