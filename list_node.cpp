#include "list_node.h"
#include "catch.hpp"

void delete_list(ListNode* head)
{
  while (head) {
    auto next = head->next;
    delete head;
    head = next;
  }
}

list_ptr create_list(std::initializer_list<int> l)
{
  auto res = list_ptr(nullptr, delete_list);

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

std::ostream& operator<<(std::ostream& os, ListNode const& l)
{
  ListNode const* node = &l;
  int count = 0;
  while (node) {
    os << (count++ ? "->" : "") << node->val;
    node = node->next;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, list_ptr const& l)
{
  return os << *l.get();
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

TEST_CASE("ListNode work properly", "[ListNode]")
{
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
    std::ostringstream ostr;
    ostr << *l1.get();
    REQUIRE("1->2->3->4->5" == ostr.str());
  }

  {
    auto l1 = create_list(1, 2, 3, 4, 5);
    auto l2 = create_list(1, 2, 3, 4, 5);
    auto l3 = create_list(1, 2, 3, 4);
    REQUIRE(l1 == l2);
    REQUIRE(l1 != l3);
  }
}
