#ifndef CONTAINERS_STACK_H_
#define CONTAINERS_STACK_H_

#include "list.h"
namespace containers {
template <class Val>
class stack : list<Val> {
 public:
  using value_type = Val;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using th = list<value_type>;

  stack() : list<value_type>(){};
  stack(std::initializer_list<value_type> const &items)
      : list<value_type>(items){};
  stack(const stack &l) : list<value_type>(l){};
  stack(stack &&l) : list<value_type>(l){};

  const_reference top() { return *(th::cend()); };

  bool empty() { return th::empty(); };
  size_type size() { return th::size(); };

  void push(const_reference value) { th::push_back(value); };
  void pop() { th::pop_back(); };
  template <class... Args>
  void insert_many_front(Args &&...args) {
    th::insert_many_back(args...);
  }
  void swap(stack<value_type> &other) { th::swap(other); };
};
}  // namespace containers

#endif  // CONTAINERS_STACK_H_
