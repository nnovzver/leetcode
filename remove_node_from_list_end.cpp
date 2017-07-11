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

struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

using list_ptr = std::unique_ptr<ListNode, void(*)(ListNode* head)>;

ListNode* create_list_impl()
{
  return nullptr;
}

template <typename T>
ListNode* create_list_impl(T one)
{
  return new ListNode(one);
}

template <typename T, typename... Ts>
ListNode* create_list_impl(T first, Ts... args)
{
  ListNode* res = new ListNode(first);
  res->next = create_list_impl(args...);

  return res;
}

template <typename... Ts>
list_ptr create_list(Ts... args)
{
  auto res = list_ptr(nullptr,
    [](ListNode* head){
      while (head) {
        auto next = head->next;
        delete head;
        head = next;
      }
    });

  res.reset(create_list_impl(args...));
  return res;
}

list_ptr create_list(std::initializer_list<int> l)
{
  auto res = list_ptr(nullptr,
    [](ListNode* head){
      while (head) {
        auto next = head->next;
        delete head;
        head = next;
      }
    });

  ListNode* cur = nullptr;
  for (auto i = l.begin(); i != l.end(); ++i) {
    if (i == l.begin()) {
      res.reset(new ListNode(*i));
      cur = res.get();
    }
    else {
      cur->next = new ListNode(*i);
      cur = cur->next;
    }
  }

  return res;
}

std::ostream& operator<<(std::ostream& os, list_ptr const& l)
{
  ListNode* node = l.get();
  int count = 0;
  while (node) {
    os << (count++ ? "->" : "") << node->val;
    node = node->next;
  }
  return os;
}

bool operator==(ListNode const& lhs, ListNode const& rhs)
{
  if (&lhs == &rhs) return true;

  ListNode const* first = &lhs;
  ListNode const* second = &rhs;

  while (first && second) {
    // if not equal values
    if (first->val != second->val) return false;
    first = first->next;
    second = second->next;
  }

  // if not equal sizes
  if (first || second) {
    return false;
  }

  return true;
}

bool operator==(list_ptr const& lhs, list_ptr const& rhs)
{
  return *lhs.get() == *rhs.get();
}

bool operator!=(list_ptr const& lhs, list_ptr const& rhs)
{
  return !(lhs == rhs);
}

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
    auto l1 = create_list({1, 2, 3, 4, 5});
    auto l2 = create_list(1, 2, 3, 4, 5);
    REQUIRE(l1 == l2);
  }

  {
    auto l1 = create_list(1, 2, 3, 4, 5);
    std::ostringstream ostr;
    ostr << l1;
    REQUIRE("1->2->3->4->5" == ostr.str());
  }

  {
    auto l1 = create_list(1, 2, 3, 4, 5);
    auto l2 = create_list(1, 2, 3, 4, 5);
    auto l3 = create_list(1, 2, 3, 4);
    REQUIRE(l1 == l2);
    REQUIRE(l1 != l3);
  }

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
