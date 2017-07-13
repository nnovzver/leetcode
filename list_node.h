#include <memory>
#include <initializer_list>
#include <sstream>

struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

using list_ptr = std::unique_ptr<ListNode, void(*)(ListNode* head)>;

void delete_list(ListNode* head);

namespace detail
{
inline ListNode* create_list_impl()
{
  return nullptr;
}

template <typename T, typename... Ts>
ListNode* create_list_impl(T first, Ts... args)
{
  ListNode* res = new ListNode(first);
  res->next = create_list_impl(args...);

  return res;
}
} // namespace detail

template <typename... Ts>
list_ptr create_list(Ts... args)
{
  auto res = list_ptr(nullptr, delete_list);

  res.reset(detail::create_list_impl(args...));
  return res;
}


list_ptr create_list(std::initializer_list<int> l);

std::ostream& operator<<(std::ostream& os, list_ptr const& l);

bool operator==(ListNode const& lhs, ListNode const& rhs);

bool operator==(list_ptr const& lhs, list_ptr const& rhs);

bool operator!=(list_ptr const& lhs, list_ptr const& rhs);
