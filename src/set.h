#ifndef CONTAINERS_SET_H_
#define CONTAINERS_SET_H_

#include "./lib/avl_tree.h"

namespace containers {
template <class T>
class SetComparator {
 public:
  using const_reference = const T &;
  static bool less(const_reference vl1, const_reference vl2) {
    return vl1 < vl2;
  }
  static bool eql(const_reference vl1, const_reference vl2) {
    return vl1 == vl2;
  }
  static bool larg(const_reference vl1, const_reference vl2) {
    return vl1 > vl2;
  }
};

template <class Key>
class set : public tree_helper<Key, SetComparator<Key>> {
 public:
  using th = tree_helper<Key, SetComparator<Key>>;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = TreeIterator<value_type, value_type *, reference>;
  using const_iterator =
      TreeIterator<value_type, const value_type *, const_reference>;
  using size_type = size_t;
  using _Self = set<value_type>;

  set(){};
  set(std::initializer_list<value_type> const &items) : th(items){};

  iterator find(const key_type &key) {
    TreeNodeClass<value_type> *it = th::_tree->getNode(key);
    return iterator(it);
  }

  bool contains(const key_type &key) {
    return th::_tree->contains(value_type{key});
  };
};
}  // namespace containers

#endif  // CONTAINERS_SET_H_
