#ifndef CONTAINERS_QUEUE_H_
#define CONTAINERS_QUEUE_H_

#include "list.h"

namespace containers {
template <class Val>
class queue : list<Val> {
 public:
  using value_type = Val;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using th = list<value_type>;

  queue() : th::list<value_type>(){};
  queue(std::initializer_list<value_type> const &items)
      : list<value_type>(items){};
  queue(const queue &l) : list<value_type>(l){};
  queue(queue &&l) : list<value_type>(l){};
  const_reference front() { return *(th::begin()); };
  const_reference back() { return *(th::end()); };
  bool empty() { return th::empty(); };
  size_type size() { return th::size(); };
  void push(const_reference value) { th::push_back(value); };
  void pop() { th::pop_front(); };

  template <class... Args>
  void insert_many_back(Args &&...args) {
    th::insert_many_back(args...);
  }

  void swap(queue<value_type> &other) { th::swap(other); };
};
}  // namespace containers
#endif  // CONTAINERS_QUEUE_H_
