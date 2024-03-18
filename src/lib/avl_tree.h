
#ifndef CONTAINERS_LIB_AVL_TREE_H_
#define CONTAINERS_LIB_AVL_TREE_H_

#include <iostream>
#include <limits>
#include <memory>

namespace containers {

template <class Value>
class TreeNodeClass {
 public:
  int h;
  TreeNodeClass *l;
  TreeNodeClass *r;
  TreeNodeClass *prev;
  TreeNodeClass *next;
  Value value;
  TreeNodeClass() : value(Value{}) { clearData(); };
  TreeNodeClass(const Value &k) : value(k) { clearData(); };

 private:
  void clearData() {
    l = r = 0;
    h = 1;
    prev = next = nullptr;
  };
};

template <class Value, class Pointer, class Reference>
class TreeIterator {
 public:
  using iterator_category = std::input_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = Value;
  using pointer = Pointer;
  using reference = Reference;
  using iterator = TreeIterator<Value, Pointer, Reference>;
  using TreeNode = TreeNodeClass<value_type>;

  TreeNode *_TreeNode;
  TreeNode *_prev = nullptr;
  TreeNode *_next = nullptr;

  TreeIterator() : _TreeNode(nullptr){};
  TreeIterator(TreeNode *p) : _TreeNode(p) {
    if (p) {
      _prev = p->prev;
      _next = p->next;
    }
  };
  TreeIterator(const iterator &it) : TreeIterator(it._TreeNode){};

  bool operator!=(iterator const &other) const {
    return _TreeNode != other._TreeNode;
  };
  bool operator==(iterator const &other) const {
    return _TreeNode == other._TreeNode;
  };
  reference operator*() const { return _TreeNode->value; };
  pointer operator->() { return &_TreeNode->value; };
  iterator &operator++() {
    _TreeNode = _next;
    _next = _TreeNode->next;
    _prev = _TreeNode->prev;
    return *this;
  };

  iterator operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
  };

  iterator &operator--() {
    _TreeNode = _prev;
    _prev = _TreeNode->prev;
    _next = _TreeNode->next;
    return *this;
  };

  iterator operator--(int) {
    iterator tmp = *this;
    --(*this);
    return tmp;
  };

  iterator operator=(const iterator &m) {
    _TreeNode = m._TreeNode;
    _next = m._next;
    _prev = m._prev;
    return *this;
  };

  value_type value() { return _TreeNode->value; }
};

template <class Val, class Comparator>
class tree {
 public:
  using value_type = Val;
  using size_type = size_t;
  using TreeNode = TreeNodeClass<value_type>;

  TreeNode *_root;
  TreeNode *_end;

  size_type size();
  size_type max_size();

  tree() {
    _root = nullptr;
    _end = new TreeNode();
    _end->next = _end->prev = _end;
    _size = 0;
  }
  ~tree() {
    if (_end) delete _end;
  }
  int height(TreeNode *p);
  int bfactor(TreeNode *p);
  void fixh(TreeNode *p);
  TreeNode *RRotate(TreeNode *p);
  TreeNode *LRotate(TreeNode *q);

  void clear();
  std::pair<TreeNode *, bool> insert(const value_type &k);
  std::pair<TreeNode *, bool> insertMS(const value_type &k);
  TreeNode *getNode(const value_type &k);
  void remove(value_type k);
  TreeNode *findMin();
  TreeNode *findMax();
  bool contains(const value_type &k);

 private:
  TreeNode *getNode(TreeNode *p, const value_type &k);
  void clear(TreeNode *p);
  bool contains(TreeNode *p, const value_type &key);
  TreeNode *Balance(TreeNode *p);
  TreeNode *insert(TreeNode *root, TreeNode *newnode, TreeNode *prnt);
  TreeNode *remove(TreeNode *p, value_type k);
  TreeNode *findMin(TreeNode *p);
  TreeNode *findMax(TreeNode *p);
  TreeNode *rmMin(TreeNode *p);
  size_type _size;
};

#include "avl_tree.tpp"
}  // namespace containers

#endif  // CONTAINERS_LIB_AVL_TREE_H
