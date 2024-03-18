#include "../list.h"

template <class Val>
list<Val>::list(){};

template <class Val>
list<Val>::list(size_type n) {
  for (size_t i = 0; i < n; i++) {
    // push_back(value_type{});
  }
};

template <class Val>
list<Val>::list(std::initializer_list<value_type> const& items) {
  for (value_type itm : items) {
    push_back(itm);
  }
};

template <class Val>
list<Val>::list(const list<Val>& l) {
  if (!l.empty()) {
    list<Val>::iterator itr = l.begin();
    push_back(itr._node->value);
    for (auto start{++itr}; start != l.begin(); start++) {
      push_back(start._node->value);
    }
  }
};

template <class Val>
list<Val>::list(list&& l) {
  _head = l._head;
  _size = l._size;
  l._head = nullptr;
  l._size = 0;
};

template <class Val>
list<Val>::~list() {
  if (_head) clear();
};

template <class Val>
list<Val>& list<Val>::operator=(list&& l) {
  if (this != &l) {
    clear();
    _head = l._head;
    l._head = nullptr;
  }
  return *this;
};

template <class Val>
typename list<Val>::const_reference list<Val>::front() {
  if (_head)
    return _head->value;
  else
    return _clr_value;
};

template <class Val>
typename list<Val>::const_reference list<Val>::back() {
  if (_head)
    return _head->_prev->value;
  else
    return _clr_value;
};

template <class Val>
typename list<Val>::iterator list<Val>::begin() const {
  return iterator(_head);
};

template <class Val>
typename list<Val>::iterator list<Val>::end() const {
  return iterator(_head->_prev);
};
template <class Val>
typename list<Val>::const_iterator list<Val>::cbegin() const {
  return const_iterator(_head);
};

template <class Val>
typename list<Val>::const_iterator list<Val>::cend() const {
  return const_iterator(_head->_prev);
};

template <class Val>
bool list<Val>::empty() const {
  return _head ? false : true;
};

template <class Val>
typename list<Val>::size_type list<Val>::size() const {
  return _size;
};

template <class Val>
typename list<Val>::size_type list<Val>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(ListNode);
};

template <class Val>
void list<Val>::clear() {
  if (_head) {
    _head->_prev->_next = nullptr;
    while (_head) {
      ListNode* tmp = _head;
      _head = _head->_next;
      delete tmp;
      tmp = nullptr;
    }
  }
};

template <class Val>
typename list<Val>::iterator list<Val>::insert(iterator pos,
                                               const_reference value) {
  append(pos._node, value);
  if (pos._node == _head) _head = _head->_prev;
  return --pos;
};

template <class Val>
template <class... Args>
typename list<Val>::iterator list<Val>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  ListNode* ln = nullptr;
  for (auto& arg : {args...}) {
    append(pos._node, arg);
    if (!ln) {
      ln = pos._node->_prev;
      if (pos._node == _head) _head = ln;
    }
  }
  return list<Val>::iterator(ln);
};

template <class Val>
template <class... Args>
void list<Val>::insert_many_back(Args&&... args) {
  for (auto& arg : {args...}) {
    push_back(arg);
  }
};

template <class Val>
template <class... Args>
void list<Val>::insert_many_front(Args&&... args) {
  insert_many(cbegin(), args...);
};

template <class Val>
void list<Val>::erase(iterator pos) {
  remove(pos._node);
};

template <class Val>
void list<Val>::push_back(const_reference value) {
  append(_head, value);
};

template <class Val>
void list<Val>::pop_back() {
  erase(end());
};

template <class Val>
void list<Val>::push_front(const_reference value) {
  append(_head, value);
  _head = _head->_prev;
};

template <class Val>
void list<Val>::pop_front() {
  erase(begin());
};

template <class Val>
void list<Val>::swap(list& other) {
  ListNode* tmp = other._head;
  other._head = _head;
  _head = tmp;
  size_type stmp = other._size;
  other._size = _size;
  _size = stmp;
};

template <class Val>
void list<Val>::merge(list& other) {
  if (!other.empty()) {
    insertList(_head, other);
  }
};

template <class Val>
void list<Val>::splice(const_iterator pos, list& other) {
  if (!other.empty()) {
    if (pos._node == _head) _head = other._head;
    insertList(pos._node, other);
  }
};

template <class Val>
void list<Val>::reverse() {
  if (!empty()) {
    _head = _head->_prev;
    ListNode* tmp = _head;
    for (size_type i = 0; i < size(); i++) {
      ListNode* t = tmp->_next;
      tmp->_next = tmp->_prev;
      tmp->_prev = t;
      tmp = tmp->_next;
    }
  }
};

template <class Val>
void list<Val>::unique() {
  if (_head) {
    removeCloneAfter(_head);
    ListNode* tmp = _head->_next;
    while (tmp != _head) {
      removeCloneAfter(tmp);
      tmp = tmp->_next;
    }
  }
};

template <class Val>
void list<Val>::sort() {
  if (_head) {
    size_type cnt = size();
    for (size_type i = 0; i < cnt - 1; i++) {
      ListNode* start = _head;
      for (size_type j = 0; j < cnt - i; j++) {
        if (start->value > start->_next->value)
          switchNode(start, start->_next);
        else
          start = start->_next;
      }
    }
  }
};

template <class Val>
void list<Val>::append(ListNode* p, const Val& v) {
  ListNode* ln = new ListNode(v);
  append(p, ln);
};

template <class Val>
void list<Val>::append(ListNode* p, ListNode* node) {
  if (!p) {
    _head = node;
    node->_next = node->_prev = node;
  } else {
    node->_next = p;
    p->_prev->_next = node;
    node->_prev = p->_prev;
    p->_prev = node;
  }
  _size++;
};

template <class Val>
void list<Val>::removeCloneAfter(ListNode* l) {
  if (l) {
    ListNode* tmp = l->_next;
    while (tmp != _head) {
      if (tmp->value == l->value) {
        ListNode* dtmp = tmp->_next;
        remove(tmp);
        tmp = dtmp;
      } else {
        tmp = tmp->_next;
      }
    }
  }
};

template <class Val>
void list<Val>::remove(ListNode* l) {
  if (l) {
    if (l->_next == l) {
      delete _head;
      _head = nullptr;
    } else {
      if (l == _head) _head = l->_next;
      l->_next->_prev = l->_prev;
      l->_prev->_next = l->_next;
      delete l;
      l = nullptr;
    }
    _size--;
  }
};

template <class Val>
void list<Val>::switchNode(ListNode* l, ListNode* p) {
  if (l == _head) _head = p;
  l->_prev->_next = p;
  p->_prev = l->_prev;
  p->_next->_prev = l;
  l->_next = p->_next;
  l->_prev = p;
  p->_next = l;
};

template <class Val>
void list<Val>::insertList(ListNode* p, list& other) {
  ListNode* ln = other._head;
  for (size_type i = 0; i < other.size(); i++) {
    ListNode* tmp = ln->_next;
    append(p, ln);
    ln = tmp;
  }
  other._size = 0;
  other._head = nullptr;
}
