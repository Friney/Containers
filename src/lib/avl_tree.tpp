#include "avl_tree.h"

template <class Val, class Comparator>
int tree<Val, Comparator>::height(TreeNode *p) {
  return p ? p->h : 0;
}

template <class Val, class Comparator>
int tree<Val, Comparator>::bfactor(TreeNode *p) {
  return height(p->r) - height(p->l);
}

template <class Val, class Comparator>
void tree<Val, Comparator>::fixh(TreeNode *p) {
  int hl = height(p->l);
  int hr = height(p->r);
  p->h = (hl > hr ? hl : hr) + 1;
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *
tree<Val, Comparator>::RRotate(TreeNode *p) {
  TreeNode *q = p->l;
  p->l = q->r;
  q->r = p;
  fixh(p);
  fixh(q);
  return q;
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *
tree<Val, Comparator>::LRotate(TreeNode *q) {
  TreeNode *p = q->r;
  q->r = p->l;
  p->l = q;
  fixh(q);
  fixh(p);
  return p;
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *
tree<Val, Comparator>::Balance(TreeNode *p) {
  TreeNode *res = p;
  fixh(p);
  if (bfactor(p) == 2) {
    if (bfactor(p->r) < 0) p->r = RRotate(p->r);
    res = LRotate(p);
  }
  if (bfactor(p) == -2) {
    if (bfactor(p->l) > 0) p->l = LRotate(p->l);
    res = RRotate(p);
  }
  return res;
}

template <class Val, class Comparator>
bool tree<Val, Comparator>::contains(const value_type &k) {
  return getNode(k) ? true : false;
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *tree<Val, Comparator>::insert(
    TreeNode *root, TreeNode *newnode, TreeNode *prnt) {
  TreeNode *res = nullptr;
  if (!root) {
    res = newnode;
    if (prnt) {
      if (Comparator::less(newnode->value, prnt->value)) {
        newnode->next = prnt;
        newnode->prev = prnt->prev;
        prnt->prev = newnode;
        newnode->prev->next = newnode;
      } else {
        newnode->prev = prnt;
        newnode->next = prnt->next;
        prnt->next = newnode;
        newnode->next->prev = newnode;
      }
    } else {
      newnode->next = newnode->prev = _end;
      _end->next = _end->prev = newnode;
    }
  } else {
    if (Comparator::less(newnode->value, root->value)) {
      root->l = insert(root->l, newnode, root);
      res = Balance(root);
    } else {
      root->r = insert(root->r, newnode, root);
      res = Balance(root);
    }
  }
  return res;
}

template <class Val, class Comparator>
std::pair<typename tree<Val, Comparator>::TreeNode *, bool>
tree<Val, Comparator>::insert(const value_type &k) {
  std::pair<TreeNode *, bool> res{nullptr, false};
  TreeNode *tn = getNode(k);
  if (!tn) {
    TreeNode *newnode = new TreeNode(k);
    _root = insert(_root, newnode, nullptr);
    _size++;
    res.first = newnode;
    res.second = true;
  } else {
    res.first = tn;
  }
  return res;
}

template <class Val, class Comparator>
std::pair<typename tree<Val, Comparator>::TreeNode *, bool>
tree<Val, Comparator>::insertMS(const value_type &k) {
  TreeNode *newnode = new TreeNode(k);
  _root = insert(_root, newnode, nullptr);
  _size++;
  return std::pair<TreeNode *, bool>{newnode, true};
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *
tree<Val, Comparator>::findMin() {
  return _root ? findMin(_root) : nullptr;
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *
tree<Val, Comparator>::findMax() {
  return _root ? findMax(_root) : nullptr;
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *
tree<Val, Comparator>::findMin(TreeNode *p) {
  return p->l ? findMin(p->l) : p;
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *
tree<Val, Comparator>::findMax(TreeNode *p) {
  return p->r ? findMax(p->r) : p;
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *tree<Val, Comparator>::rmMin(
    TreeNode *p) {
  TreeNode *res;
  if (!p->l) {
    res = p->r;
  } else {
    p->l = rmMin(p->l);
    res = Balance(p);
  }
  return res;
}

template <class Val, class Comparator>
void tree<Val, Comparator>::clear(TreeNode *p) {
  if (p) {
    clear(p->l);
    clear(p->r);
    delete p;
  }
}

template <class Val, class Comparator>
void tree<Val, Comparator>::clear() {
  if (_root) {
    clear(_root);
    _root = nullptr;
  }

  _end->next = _end->prev = _end;
  _size = 0;
}

template <class Val, class Comparator>
void tree<Val, Comparator>::remove(value_type k) {
  _root = remove(_root, k);
  _size--;
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *tree<Val, Comparator>::remove(
    TreeNode *p, value_type k) {
  TreeNode *res = nullptr;
  if (p) {
    if (Comparator::less(k, p->value)) {
      p->l = remove(p->l, k);
      res = Balance(p);
    } else if (Comparator::larg(k, p->value)) {
      p->r = remove(p->r, k);
      res = Balance(p);
    } else {
      TreeNode *q = p->l;
      TreeNode *r = p->r;
      p->next->prev = p->prev;
      p->prev->next = p->next;
      delete p;
      p = nullptr;
      if (!r)
        res = q;
      else {
        TreeNode *min = findMin(r);
        min->r = rmMin(r);
        min->l = q;
        res = Balance(min);
      }
    }
  }
  return res;
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *
tree<Val, Comparator>::getNode(const value_type &k) {
  return getNode(_root, k);
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::TreeNode *
tree<Val, Comparator>::getNode(TreeNode *p, const value_type &k) {
  TreeNode *res = nullptr;
  if (p) {
    if (Comparator::eql(p->value, k))
      res = p;
    else if (Comparator::less(p->value, k))
      res = getNode(p->r, k);
    else
      res = getNode(p->l, k);
  }
  return res;
}

template <class Val, class Comparator>
typename tree<Val, Comparator>::size_type
tree<Val, Comparator>::size() {
  return _size;
};

template <class Val, class Comparator>
typename tree<Val, Comparator>::size_type
tree<Val, Comparator>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(TreeNode);
};
