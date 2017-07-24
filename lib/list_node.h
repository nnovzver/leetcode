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
inline ListNode* create_list_impl(bool&) noexcept
{
  return nullptr;
}

template <typename T, typename... Ts>
ListNode* create_list_impl(bool& bad_list, T first, Ts... args) noexcept
{
  ListNode* res = new(std::nothrow) ListNode(first);
  if (res == nullptr) {
    bad_list = true;
    return nullptr;
  }

  res->next = create_list_impl(bad_list, args...);
  if (bad_list) {
    delete res;
    return nullptr;
  }

  return res;
}
} // namespace detail

template <typename... Ts>
list_ptr create_list(Ts... args) noexcept
{
  bool bad_list = false;
  return list_ptr(detail::create_list_impl(bad_list, args...), delete_list);
}


list_ptr create_list(std::initializer_list<int> l);

std::ostream& operator<<(std::ostream& os, list_ptr const& l);
std::ostream& operator<<(std::ostream& os, ListNode const& l);

bool operator==(ListNode const& lhs, ListNode const& rhs);

bool operator==(list_ptr const& lhs, list_ptr const& rhs);

bool operator!=(list_ptr const& lhs, list_ptr const& rhs);
