// Reverse Nodes in k-Group

// Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

// k is a positive integer and is less than or equal to the length of the linked list.
// If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

// You may not alter the values in the nodes, only nodes itself may be changed.

// Only constant memory is allowed.

// For example,
// Given this linked list: 1->2->3->4->5

// For k = 2, you should return: 2->1->4->3->5

// For k = 3, you should return: 3->2->1->4->5

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <utility>
#include "list_node.h"
#include "catch.hpp"

class Solution
{
public:
  ListNode* reverseKGroup_iter(ListNode* cur, int k)
  {
    if (k == 0) {
      return nullptr;
    }
    if (cur == nullptr) {
      return nullptr;
    }

    ListNode* tail = reverseKGroup_iter(cur->next, k-1);
    if (tail) {
      cur->next = nullptr;
      tail->next = cur;
    }
    return cur;
  }

  bool isListReversable(ListNode* head, int k, ListNode*& first, ListNode*& nextGroup)
  {
    int counter = k;
    ListNode* i = head;
    while (i) {
      --counter;
      if (counter == 0) break;
      i = i->next;
    }

    if (counter == 0) {
      first = i;
      nextGroup = i->next;
      return true;
    }
    else {
      first = head;
      nextGroup = nullptr;
      return false;
    }
  }

  ListNode* reverseKGroup(ListNode* head, int k)
  {
    ListNode* ret = head;
    ListNode* nextGroup = nullptr;

    bool isreversable = isListReversable(head, k, ret, nextGroup);
    if (not isreversable) {
      return head;
    }

    ListNode* tail;
    do {
      tail = reverseKGroup_iter(head, k);
      head = nextGroup;
    } while (isListReversable(head, k, tail->next, nextGroup));
    return ret;
  }
};

TEST_CASE("reverseKGroup works properly")
{
  Solution sol;

  {
    ListNode* l = create_list(1, 2, 3).release();
    auto res = create_list(1, 2, 3);
    ListNode* ret = sol.reverseKGroup(l, 4);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }

  {
    ListNode* l = create_list(1, 2, 3).release();
    auto res = create_list(3, 2, 1);
    ListNode* ret = sol.reverseKGroup(l, 3);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }

  {
    ListNode* l = create_list(1, 2, 3).release();
    auto res = create_list(2, 1, 3);
    ListNode* ret = sol.reverseKGroup(l, 2);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }

  {
    ListNode* l = create_list(1, 2, 3).release();
    auto res = create_list(1, 2, 3);
    ListNode* ret = sol.reverseKGroup(l, 1);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }

  {
    ListNode* l = create_list(1, 2, 3, 4).release();
    auto res = create_list(2, 1, 4, 3);
    ListNode* ret = sol.reverseKGroup(l, 2);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }

  {
    ListNode* l = create_list(1, 2, 3, 4, 5, 6, 7, 8).release();
    auto res = create_list(3, 2, 1, 6, 5, 4, 7, 8);
    ListNode* ret = sol.reverseKGroup(l, 3);
    REQUIRE(*res.get() == *ret);
    delete_list(ret);
  }
}
