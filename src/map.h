#ifndef CONTAINERS_MAP_H_
#define CONTAINERS_MAP_H_

#include "./lib/tree_helper.h"

namespace containers {
template <class Key, class T>
class MapComparator {
 public:
  using value_type = std::pair<const Key, T>;
  using const_reference = const value_type &;
  static bool less(const_reference vl1, const_reference vl2) {
    return vl1.first < vl2.first;
  }
  static bool eql(const_reference vl1, const_reference vl2) {
    return vl1.first == vl2.first;
  }
  static bool larg(const_reference vl1, const_reference vl2) {
    return vl1.first > vl2.first;
  }
};

template <class Key, class T>
class map
    : public tree_helper<std::pair<const Key, T>, MapComparator<Key, T>> {
 public:
  using th = tree_helper<std::pair<const Key, T>, MapComparator<Key, T>>;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using TreeNode = TreeNodeClass<value_type>;
  using iterator = TreeIterator<value_type, value_type *, reference>;
  using const_iterator =
      TreeIterator<value_type, const value_type *, const_reference>;

  map(){};
  map(std::initializer_list<value_type> const &items) : th(items){};

  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &val) {
    return th::_tree->insert(value_type{key, val});
  };

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
    std::pair<iterator, bool> res{nullptr, true};
    TreeNode *tn = th::_tree->getNode(value_type{key, obj});
    if (tn) {
      tn->value.second = obj;
      res.first = iterator(tn);
    } else {
      res = th::insert(value_type{key, obj});
    }
    return res;
  };

  T &at(const key_type &key) {
    TreeNode *it = th::_tree->getNode(value_type{key, mapped_type()});
    if (it == nullptr) throw std::out_of_range("out_of_range");
    return it->value.second;
  };

  T &operator[](const key_type &key) {
    TreeNode *tn = th::_tree->getNode(value_type{key, mapped_type()});
    if (!tn) {
      auto n = insert(key, mapped_type());
      tn = n.first._TreeNode;
    }
    return tn->value.second;
  };

  bool contains(const key_type &key) {
    return th::_tree->contains(value_type{key, mapped_type()});
  };
};
}  // namespace containers

#endif  // CONTAINERS_MAP_H
