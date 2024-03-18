#ifndef CONTAINERS_LIB_TREE_HELPER_H_
#define CONTAINERS_LIB_TREE_HELPER_H_

#include "../vector.h"
#include "avl_tree.h"
namespace containers {
template <class Value, class Comparator>
class tree_helper {
 public:
  using value_type = Value;
  using reference = value_type &;
  using pointer = value_type *;
  using const_reference = const value_type &;
  using const_pointer = const value_type *;
  using iterator = TreeIterator<value_type, pointer, reference>;
  using const_iterator =
      TreeIterator<value_type, const_pointer, const_reference>;

  using size_type = std::size_t;
  using TreeNode = TreeNodeClass<value_type>;
  using Tree = tree<value_type, Comparator>;

  tree_helper() : _tree(new Tree()){};

  tree_helper(std::initializer_list<value_type> const &items)
      : tree_helper() {
    for (value_type itm : items) {
      _tree->insert(itm);
    }
  };

  tree_helper(const tree_helper &m) : tree_helper() {
    for (auto start{m.begin()}; start != m.end(); start++) {
      _tree->insert(start._TreeNode->value);
    }
  };

  tree_helper(tree_helper &&m) : tree_helper() {
    if (_tree) {
      delete _tree;
    }
    _tree = m._tree;
    m._tree = nullptr;
  };

  ~tree_helper() {
    if (_tree) {
      _tree->clear();
      delete _tree;
    }
  };

  tree_helper &operator=(const tree_helper &m) {
    clear();
    for (auto start{m.begin()}; start != m.end(); start++) {
      _tree->insert(start._TreeNode->value);
    }
    return *this;
  };

  iterator begin() const { return ++(iterator(_tree->_end)); };
  iterator end() const { return iterator(_tree->_end); };

  const_iterator cbegin() const { return ++(const_iterator(_tree->_end)); };
  const_iterator cend() const { return const_iterator(_tree->_end); };

  bool empty() { return size() == 0; }

  size_type size() { return _tree->size(); };
  size_type max_size() { return _tree->max_size(); };

  void clear() { _tree->clear(); };

  std::pair<iterator, bool> insert(const value_type &value) {
    std::pair<TreeNode *, bool> res = _tree->insert(value);
    return {iterator(res.first), res.second};
  };

  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    vector<std::pair<iterator, bool>> res;
    for (auto &arg : {args...}) {
      res.push_back(insert(arg));
    }
    return res;
  }

  void erase(iterator pos) {
    _tree->remove(pos.value());
    pos._TreeNode = pos._next = pos._prev = nullptr;
  };

  void swap(tree_helper &other) {
    Tree *tmp = this->_tree;
    this->_tree = other._tree;
    other._tree = tmp;
  };

  void merge(tree_helper &other) {
    for (auto start{other.begin()}; start != other.end(); start++) {
      insert(start._TreeNode->value);
    }
    other.clear();
  }

 protected:
  std::pair<iterator, bool> insertMS(const value_type &k) {
    std::pair<TreeNode *, bool> res = _tree->insertMS(k);
    return {iterator(res.first), res.second};
  };
  Tree *_tree;
};
}  // namespace containers

#endif  // CONTAINERS_LIB_TREE_HELPER_H
