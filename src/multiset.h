#ifndef CONTAINERS_MULTISET_H_
#define CONTAINERS_MULTISET_H_

#include "./lib/avl_tree.h"
#include "set.h"

namespace containers {
template <class Key>
class multiset : public tree_helper<Key, SetComparator<Key>> {
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
  using _Self = multiset<value_type>;

  using TreeNode = TreeNodeClass<value_type>;

  multiset(){};
  multiset(std::initializer_list<value_type> const &items) : multiset() {
    for (value_type itm : items) {
      th::_tree->insertMS(itm);
    }
  };

  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    vector<std::pair<iterator, bool>> res;
    for (auto &arg : {args...}) {
      res.push_back(th::_tree->insertMS(arg));
    }
    return res;
  };

  std::pair<iterator, bool> insert(const value_type &value) {
    return th::insertMS(value);
  };

  size_type count(const Key &key) {
    multiset<Key>::iterator upi = upper_bound(key);
    int res = 0;
    for (auto start{lower_bound(key)}; start != upi; start++) res++;
    return res;
  };

  iterator find(const key_type &key) {
    TreeNodeClass<value_type> *it = th::_tree->getNode(key);
    return iterator(it);
  };

  bool contains(const key_type &key) {
    return th::_tree->contains(value_type{key});
  };

  std::pair<iterator, iterator> equal_range(const Key &key) {
    return std::pair<iterator, iterator>{lower_bound(key), upper_bound(key)};
  };

  iterator lower_bound(const Key &key) {
    TreeNodeClass<Key> *tn = th::_tree->getNode(key);
    if (tn) {
      tn = getLower(tn, key);
    }
    return iterator(tn);
  };

  iterator upper_bound(const Key &key) {
    TreeNodeClass<Key> *tn = th::_tree->getNode(key);
    if (tn) {
      tn = getUpper(tn, key);
    }
    return iterator(tn);
  };

 protected:
  TreeNode *getLower(TreeNode *p, const value_type &k) {
    TreeNode *res = nullptr;
    if (p) {
      if (p->prev->value == k && p->prev != th::_tree->_end)
        res = getLower(p->prev, k);
      else
        res = p;
    }
    return res;
  }

  TreeNode *getUpper(TreeNode *p, const value_type &k) {
    TreeNode *res = nullptr;
    if (p) {
      if (p->next && p->next->value == k && p->next != th::_tree->_end)
        res = getUpper(p->next, k);
      else
        res = p->next;
    }
    return res;
  }
};
}  // namespace containers

#endif  // CONTAINERS_MULTISET_H
