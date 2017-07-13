// Insertion Sort List

// Sort a linked list using insertion sort.

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
  void insertionSortListImpl(ListNode* head, bool& sorted)
  {
    if (head == nullptr or head->next == nullptr) {
      sorted = true;
      return;
    }

    while (!sorted) {
      if (head->next->val < head->val) {
        std::swap(head->val, head->next->val);
        return;
      }
      insertionSortListImpl(head->next, sorted);
    }
    return;
  }

  ListNode* insertionSortList(ListNode* head)
  {
    bool sorted = false;
    while (!sorted) {
      insertionSortListImpl(head, sorted);
    }
    return head;
  }
};

TEST_CASE("insertionSortList work properly", "[insertionSortList]")
{
  Solution sol;

  {
    auto l1 = create_list();
    REQUIRE(nullptr == sol.insertionSortList(l1.get()));
  }
  {
    auto l1 = create_list(1);
    auto l2 = create_list(1);
    sol.insertionSortList(l1.get());
    REQUIRE(l2 == l1);
  }
  {
    auto l1 = create_list(2, 1);
    auto l2 = create_list(1, 2);
    sol.insertionSortList(l1.get());
    REQUIRE(l2 == l1);
  }
  {
    auto l1 = create_list(2, 3, 1);
    auto l2 = create_list(1, 2, 3);
    sol.insertionSortList(l1.get());
    REQUIRE(l2 == l1);
  }
  {
    auto l1 = create_list(3, 2, 1);
    auto l2 = create_list(1, 2, 3);
    sol.insertionSortList(l1.get());
    REQUIRE(l2 == l1);
  }
  {
    auto l1 = create_list(9, 8, 7, 6, 5, 4, 3, 2, 1);
    auto l2 = create_list(1, 2, 3, 4, 5, 6, 7, 8, 9);
    sol.insertionSortList(l1.get());
    REQUIRE(l2 == l1);
  }
  {
    auto l1 = create_list(1, 3, 5, 4, 9, 8, 6, 7, 2);
    auto l2 = create_list(1, 2, 3, 4, 5, 6, 7, 8, 9);
    sol.insertionSortList(l1.get());
    REQUIRE(l2 == l1);
  }
}
