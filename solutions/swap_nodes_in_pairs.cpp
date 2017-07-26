// Swap Nodes in Pairs

// Given a linked list, swap every two adjacent nodes and return its head.

// For example,
// Given 1->2->3->4, you should return the list as 2->1->4->3.

// Your algorithm should use only constant space.
// You may not modify the values in the list, only nodes itself can be changed.

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
  ListNode* swapPairs(ListNode* head)
  {
    ListNode* first = head;
    if (first == nullptr) return nullptr;
    ListNode* second = head->next;
    if (second == nullptr) return head;

    ListNode* res = second;
    ListNode* tail = nullptr;

    while (first != nullptr and second != nullptr) {
      first->next = second->next;
      second->next = first;
      if (tail != nullptr) {
        tail->next = second;
      }
      tail = first;

      first = tail->next;
      second = first != nullptr ? first->next : nullptr;
    }

    return res;
  }
};

TEST_CASE("swapPairs works properly", "[swapPairs]")
{
  Solution sol;

  {
    ListNode* l = create_list().release();
    REQUIRE(nullptr == sol.swapPairs(l));
    delete_list(l);
  }

  {
    ListNode* l = create_list(1).release();
    auto res = create_list(1);
    REQUIRE(*res.get() == *sol.swapPairs(l));
    delete_list(l);
  }

  {
    ListNode* l = create_list(1).release();
    auto res = create_list(1);
    REQUIRE(*res.get() == *sol.swapPairs(l));
    delete_list(l);
  }

  {
    ListNode* l = create_list(1, 2).release();
    auto res = create_list(2, 1);
    REQUIRE(*res.get() == *sol.swapPairs(l));
    delete_list(l);
  }

  {
    ListNode* l = create_list(1, 2, 3).release();
    auto res = create_list(2, 1, 3);
    REQUIRE(*res.get() == *sol.swapPairs(l));
    delete_list(l);
  }

  {
    ListNode* l = create_list(1, 2, 3, 4).release();
    auto res = create_list(2, 1, 4, 3);
    REQUIRE(*res.get() == *sol.swapPairs(l));
    delete_list(l);
  }
}
