// Remove Nth Node From End of List

// Given a linked list, remove the nth node from the end of list and return its head.

// For example,
// Given linked list: 1->2->3->4->5, and n = 2.
// After removing the second node from the end, the linked list becomes 1->2->3->5.

// Note:
// Given n will always be valid.
// Try to do this in one pass.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <memory>
#include <initializer_list>
#include <sstream>
#include "catch.hpp"
#include "list_node.h"

class Solution
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
      if (n <= 0) return head;
      if (head == nullptr) return head;

      ListNode* first = head;
      ListNode* second = head;

      for (int i = 0; i < n; ++i) {
        if (!second) return head;
        second = second->next;
      }
      // delete first
      if (!second) {
        head = first->next;
        delete first;
        return head;
      }

      while (second->next) {
        first = first->next;
        second = second->next;
      }

      ListNode* tmp = first->next->next;
      delete first->next;
      first->next = tmp;

      return head;
    }
};

TEST_CASE("removeNthFromEnd work properly", "[removeNthFromEnd]")
{
  Solution sol;

  {
    auto l1 = create_list(1, 2, 3, 4, 5);
    auto l2 = create_list(1, 2, 3, 5);
    ListNode* head = sol.removeNthFromEnd(l1.get(), 2);
    REQUIRE(head == l1.get());
    REQUIRE(l1 == l2);
  }

  {
    auto l1 = create_list();
    ListNode* head = sol.removeNthFromEnd(l1.get(), 0);
    REQUIRE(nullptr == head);
  }

  {
    auto l1 = create_list(1);
    auto l2 = create_list(1);
    sol.removeNthFromEnd(l1.get(), 0);
    REQUIRE(l1 == l2);

    ListNode* l1_ptr = l1.release();
    ListNode* head = sol.removeNthFromEnd(l1_ptr, 1);
    REQUIRE(nullptr == head);
  }

  {
    auto l1 = create_list(1, 2);
    auto l2 = create_list(1);
    sol.removeNthFromEnd(l1.get(), 1);
    REQUIRE(l1 == l2);

    ListNode* l1_ptr = l1.release();
    ListNode* head = sol.removeNthFromEnd(l1_ptr, 1);
    REQUIRE(nullptr == head);
  }
}
