#ifndef CONTAINERS_LIST_H_
#define CONTAINERS_LIST_H_

#include <iostream>
#include <limits>
#include <memory>
namespace containers {
template <class Val>
class ListNodeClass {
 public:
  ListNodeClass *_next = nullptr;
  ListNodeClass *_prev = nullptr;
  Val value;
  ListNodeClass(){};
  ListNodeClass(const Val &v) : value(v){};
};

template <class T, class ref>
class listIterator {
 public:
  using Node = ListNodeClass<T>;
  using iterator = listIterator<T, ref>;
  using reference = ref;
  using pointer = T *;
  Node *_node;
  listIterator(Node *p) : _node(p){};
  listIterator(const iterator &it) : listIterator(it._node){};

  bool operator!=(iterator const &other) const { return _node != other._node; };

  bool operator==(iterator const &other) const { return _node == other._node; };
  reference operator*() const { return _node->value; };
  pointer operator->() { return &(_node->value); };
  iterator &operator++() {
    if (_node) _node = _node->_next;
    return *this;
  };

  iterator operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
  };

  iterator &operator--() {
    if (_node) _node = _node->_prev;
    return *this;
  };

  iterator operator--(int) {
    iterator tmp = *this;
    --(*this);
    return tmp;
  };

  iterator operator=(const iterator &m) {
    _node = m._node;
    return *this;
  };
};

template <class Val>
class list {
 public:
  using ListNode = ListNodeClass<Val>;
  using value_type = Val;

  using reference = value_type &;
  using pointer = value_type *;
  using const_reference = const value_type &;
  using iterator = listIterator<value_type, reference>;
  using const_iterator = listIterator<value_type, const_reference>;
  using size_type = std::size_t;

  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list<value_type> &l);
  list(list<value_type> &&l);
  ~list();
  list &operator=(list<value_type> &&l);

  const_reference front();
  const_reference back();

  iterator begin() const;
  iterator end() const;

  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);

  inline void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list<value_type> &other);
  void merge(list<value_type> &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

 private:
  value_type _clr_value{};
  ListNode *_head = nullptr;
  size_type _size = 0;
  void append(ListNode *p, const Val &v);
  void append(ListNode *p, ListNode *node);
  void insertList(ListNode *p, list &other);
  void remove(ListNode *p);
  void removeCloneAfter(ListNode *l);
  void switchNode(ListNode *l, ListNode *p);
};

#include "./lib/list.tpp"

}  // namespace containers

#endif  // CONTAINERS_LIST_H_
