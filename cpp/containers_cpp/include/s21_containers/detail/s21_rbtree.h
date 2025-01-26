#ifndef search_tree_H_
#define search_tree_H_

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace s21 {

template <class Key, class Value = void, class Compare = std::less<Key>>
class search_tree {
  using type = search_tree<Key, Value, Compare>;

 public:
  template <bool is_const>
  class Iterator;

  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::conditional_t<std::is_void_v<Value>, Key,
                                        std::pair<const Key, Value>>;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using key_compare = Compare;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // special
  search_tree() noexcept(false)
      : nil_(new Node(value_type{}, Node::Color::black)), root_(nil_) {}
  search_tree(std::initializer_list<value_type> const& items) noexcept(false)
      : nil_(new Node(value_type{}, Node::Color::black)), root_(nil_) {
    for (auto&& elem : items) insert(elem);
  }
  search_tree(const search_tree& other) noexcept(false)
      : nil_(new Node(value_type{}, Node::Color::black)) {
    root_ = CopyRecursive(other.root_, nil_, other.nil_);
    nil_->left_ = root_;
  }
  search_tree(search_tree&& other) noexcept
      : nil_(std::exchange(other.nil_, nullptr)),
        root_(std::exchange(other.root_, nullptr)),
        n_(std::exchange(other.n_, 0)) {}
  search_tree& operator=(const search_tree& other) noexcept(false) {
    search_tree(other).swap(*this);
    return *this;
  }
  search_tree& operator=(search_tree&& other) noexcept {
    search_tree(std::move(other)).swap(*this);
    return *this;
  }
  ~search_tree() noexcept {
    if (!empty()) clear();
    delete nil_;
  }

  // special support

  void clear() noexcept { DestroyRecursive(root_); }
  void swap(search_tree& other) noexcept {
    using std::swap;
    swap(root_, other.root_);
    swap(nil_, other.nil_);
    swap(n_, other.n_);
  }
  friend void swap(const search_tree& a, const search_tree& b) noexcept {
    a.swap(b);
  }
  friend bool operator==(const search_tree& a, const search_tree& b) {
    if (&a == &b) return true;
    if (a.n_ != b.n_) return false;
    for (auto ita = a.begin(), itb = b.begin(); ita != a.end(); ++ita, ++itb) {
      if (*ita != *itb) return false;
    }
    return true;
  }
  friend bool operator!=(const search_tree& a, const search_tree& b) {
    return !operator==(a, b);
  }

 protected:
  struct Node;
  [[nodiscard]] Node* CopyRecursive(Node* node, Node* parent, Node* other_nil) {
    if (node == other_nil) return nil_;
    Node* new_node = new Node(node->data_, node->color_, parent);
    new_node->left_ = CopyRecursive(node->left_, new_node, other_nil);
    new_node->right_ = CopyRecursive(node->right_, new_node, other_nil);
    n_++;
    return new_node;
  }
  void DestroyRecursive(Node* node) noexcept {
    if (!node || node == nil_) return;
    DestroyRecursive(node->left_);
    DestroyRecursive(node->right_);
    n_--;
    delete node;
  }

  // iterators

 public:
  iterator begin() noexcept {
    if (empty()) return end();
    Node* tmp = root_;
    while (tmp->left_ != nil_) tmp = tmp->left_;
    return iterator(tmp);
  }
  const_iterator begin() const noexcept {
    if (empty()) return end();
    Node* tmp = root_;
    while (tmp->left_ != nil_) tmp = tmp->left_;
    return const_iterator(tmp);
  }
  iterator end() noexcept { return iterator(nil_); }
  const_iterator end() const noexcept { return const_iterator(nil_); }
  const_iterator cbegin() const noexcept { return begin(); }
  const_iterator cend() const noexcept { return end(); }

  reverse_iterator rbegin() noexcept { return std::reverse_iterator(end()); }
  reverse_iterator rend() noexcept { return std::reverse_iterator(begin()); }
  const_reverse_iterator rbegin() const noexcept {
    return std::reverse_iterator(end());
  }
  const_reverse_iterator rend() const noexcept {
    return std::reverse_iterator(begin());
  }
  const_reverse_iterator crbegin() const noexcept {
    return std::reverse_iterator(cend());
  }
  const_reverse_iterator crend() const noexcept {
    return std::reverse_iterator(cbegin());
  }

  // element access

  template <typename = std::enable_if<!std::is_void_v<Value>>>
  std::add_lvalue_reference_t<const mapped_type> at(const Key& key) const {
    auto pos = find(key);
    if (pos == end()) throw std::out_of_range("at(): the entry does not exist");
    return (*pos).second;
  }
  template <typename = std::enable_if<!std::is_void_v<Value>>>
  std::add_lvalue_reference_t<mapped_type> at(const Key& key) {
    return const_cast<mapped_type&>(std::as_const(*this).at(key));
  }
  template <typename = std::enable_if<!std::is_void_v<Value>>>
  std::add_lvalue_reference_t<mapped_type> operator[](const Key& key) {
    iterator pos = find(key);
    if (pos == end()) pos = insert(std::pair(key, mapped_type{}));
    return (*pos).second;
  }

  // capactiy

  [[nodiscard]] bool empty() const noexcept { return n_ == 0; }
  size_type size() const noexcept { return n_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<difference_type>::max() / sizeof(Node);
  }
  void erase(const Key& key) {
    auto pos = find(key);
    if (pos != end()) erase(pos);
  }
  void erase(iterator pos);
  void erase_all(const Key& key) {
    while (contains(key)) erase(key);
  }

  // modifiers

  iterator insert(const value_type& data);
  // use a dummy template parameter to defer a type trait evaluation
  template <typename U = Value, typename = std::enable_if<std::is_void_v<U>>>
  std::pair<iterator, bool> insert_or_assign(const Key& key, const U& obj) {
    auto pos = find(key);
    if (pos == end()) return {insert(value_type(key, obj)), true};
    (*pos).second = obj;
    return {pos, false};
  }

  template <typename U = Value, typename = std::enable_if<std::is_void_v<U>>>
  std::pair<iterator, bool> insert_if_ne(const Key& key, const U& obj) {
    auto pos = find(key);
    if (pos != end()) return {pos, false};
    return {insert(value_type(key, obj)), true};
  }
  std::pair<iterator, bool> insert_if_ne(const value_type& data) {
    auto pos = find(get_key(data));
    if (pos != end()) return {pos, false};
    return {insert(data), true};
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vec;
    for (auto&& arg : {args...}) {
      vec.push_back({insert(arg), true});
    }
    return vec;
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_if_ne_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vec;
    for (auto&& arg : {args...}) {
      vec.push_back(insert_if_ne(arg));
    }
    return vec;
  }

  void merge(search_tree& other) {
    const search_tree ctree(other);
    for (const auto& elem : ctree) {
      insert(elem);
      other.erase(get_key(elem));
    }
  }

  void merge_if_ne(search_tree& other) {
    const search_tree ctree(other);
    for (const auto& elem : ctree) {
      auto [pos, res] = insert_if_ne(elem);
      if (res) other.erase(get_key(elem));
    }
  }

  // lookup

  bool contains(const Key& key) const {
    auto pos = find(key);
    return pos != end();
  }
  size_type count(const Key& key) const {
    auto iter = find(key);
    if (iter == end()) return 0;
    if (iter == begin()) return 1;

    int count = 1;
    auto biter = iter;  // backward
    auto fiter = iter;  // forward
    while (biter != begin() && keys_equal(key, get_key(*--iter)))
      ++count, --biter;
    ++fiter;
    while (fiter != end() && keys_equal(key, get_key(*fiter))) ++count, ++fiter;

    return count;
  }
  iterator find(const Key& key);
  const_iterator find(const Key& key) const;
  iterator lower_bound(const Key& key) {
    auto iter = find(key);
    if (iter == end()) return iter;
    auto biter = iter;
    while (iter != begin() && keys_equal(key, get_key(*--biter))) --iter;
    return iter;
  }
  iterator upper_bound(const Key& key) {
    auto iter = lower_bound(key);
    while (iter != end() && keys_equal(key, get_key(*iter))) ++iter;
    return iter;
  }
  std::pair<iterator, iterator> equal_range(const Key& key) {
    return {lower_bound(key), upper_bound(key)};
  }

  // print

  friend std::ostream& operator<<(std::ostream& os,
                                  const search_tree& t) noexcept {
    t.print(os);
    return os;
  }
  void print(std::ostream& os) const noexcept {
    os << "N" << std::endl;
    if (!empty()) PrintRecursive(os, "", root_, true);
  }

 protected:
  void PrintRecursive(std::ostream& os, const std::string& prefix, Node* node,
                      bool is_left) const noexcept;

 public:
  template <bool is_const>
  class Iterator {
    friend class search_tree;
    friend class Iterator<!is_const>;

   public:
    using difference_type = search_tree::difference_type;
    using value_type = search_tree::value_type;
    using pointer =
        std::conditional_t<is_const, const value_type*, value_type*>;
    using reference =
        std::conditional_t<is_const, const value_type&, value_type&>;
    using iterator_category = std::bidirectional_iterator_tag;

    reference operator*() const noexcept { return ptr_->data_; }
    auto& operator++();
    auto operator++(int) {
      auto result = *this;
      ++*this;
      return result;
    }
    auto& operator--();
    auto operator--(int) {
      auto result = *this;
      --*this;
      return result;
    }
    template <bool R>  // allow comparisons between iterator and const_iterator
    bool operator==(const Iterator<R>& rhs) const noexcept {
      return ptr_ == rhs.ptr_;
    }
    template <bool R>
    bool operator!=(const Iterator<R>& rhs) const noexcept {
      return ptr_ != rhs.ptr_;
    }
    operator Iterator<true>() const noexcept {  // NOLINT; allow implicit conv
      return Iterator<true>(ptr_);
    }

   private:
    using node_pointer = std::conditional_t<is_const, const Node*, Node*>;
    explicit Iterator(node_pointer p) noexcept : ptr_(p){};

    node_pointer ptr_;
  };

 protected:
  static key_type get_key(const value_type& data) noexcept {
    if constexpr (std::is_void_v<Value>)
      return data;
    else
      return data.first;
  }
  static bool keys_equal(const key_type& a, const key_type& b) noexcept(false) {
    key_compare cmp;
    return !cmp(a, b) && !cmp(b, a);
  }
  void InsertFixup(Node* node) noexcept;
  void EraseFixup(Node* node) noexcept;
  Node* TrinodeRestructure(Node* node) noexcept;
  void TransplantSubtree(Node* dst, Node* src) noexcept;

  struct Node {
    friend class search_tree;
    enum Color { red, black };

    explicit Node(const value_type& v, Color c) : data_(v), color_(c) {}
    explicit Node(const value_type& v, Color c, Node* p)
        : data_(v), color_(c), parent_(p) {}

    bool is_internal() const noexcept { return right_; }
    // bool is_external() const noexcept { return !right_; }
    bool is_left() const noexcept { return parent_->left_ == this; }
    bool is_right() const noexcept { return parent_->right_ == this; }
    Node* sibling() const noexcept {
      return this->is_left() ? parent_->right_ : parent_->left_;
    }
    Node* parent() const noexcept { return parent_; }
    Node* grandparent() const noexcept { return parent_->parent_; }
    bool is_black() const noexcept { return color_ == Color::black; }
    bool is_red() const noexcept { return color_ == Color::red; }
    void set_black() noexcept { color_ = Color::black; }
    void set_red() noexcept { color_ = Color::red; }
    void set_color(Color col) noexcept { color_ = col; }

   private:
    value_type data_;
    Color color_;
    Node* parent_ = nullptr;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
  };

 private:
  Node* nil_;  // sentinel node
  Node* root_;
  size_type n_ = 0;  // true nodes (hold data provided by user)
};

template <class Key, class Value, class Compare>
typename search_tree<Key, Value, Compare>::iterator
search_tree<Key, Value, Compare>::find(const Key& key) {
  if (root_ == nil_) return end();
  Node* cur = root_;
  key_compare cmp;
  while (cur != nil_) {
    key_type cur_key = get_key(cur->data_);
    if (!cmp(key, cur_key) && !cmp(cur_key, key)) break;
    if (cmp(key, cur_key))
      cur = cur->left_;
    else
      cur = cur->right_;
  }
  return iterator(cur);
}

template <class Key, class Value, class Compare>
typename search_tree<Key, Value, Compare>::const_iterator
search_tree<Key, Value, Compare>::find(const Key& key) const {
  if (root_ == nil_) return end();
  Node* cur = root_;
  key_compare cmp;
  while (cur != nil_) {
    key_type cur_key = get_key(cur->data_);
    if (!cmp(key, cur_key) && !cmp(cur_key, key)) break;
    if (cmp(key, cur_key))
      cur = cur->left_;
    else
      cur = cur->right_;
  }
  return iterator(cur);
}

template <class Key, class Value, class Compare>
typename search_tree<Key, Value, Compare>::iterator
search_tree<Key, Value, Compare>::insert(const value_type& data) {
  if (root_ == nil_) {
    root_ = new Node(data, Node::Color::black), n_++;
    root_->parent_ = root_->left_ = root_->right_ = nil_;
    nil_->left_ = root_;
    return iterator(root_);
  }

  Node* cur = root_;
  Node* par = nil_;
  key_compare cmp;
  bool is_smaller;

  while (cur != nil_) {
    par = cur;
    is_smaller = cmp(get_key(data), get_key(cur->data_));
    if (is_smaller)
      cur = cur->left_;
    else
      cur = cur->right_;
  }

  Node* node = new Node(data, Node::Color::red);
  n_++;
  node->left_ = node->right_ = nil_;
  node->parent_ = par;
  if (is_smaller)
    par->left_ = node;
  else
    par->right_ = node;

  InsertFixup(node);
  return iterator(node);
}

template <class K, class V, class C>
void search_tree<K, V, C>::InsertFixup(Node* node) noexcept {
  Node* p = node->parent_;
  if (p == root_ || p->is_black()) return;
  if (p->sibling()->is_black()) {
    p = TrinodeRestructure(node);
    p->set_black();
    p->left_->set_red();
    p->right_->set_red();
  } else {
    p->set_black();
    p->sibling()->set_black();
    Node* g = p->parent_;
    if (g == root_) return;
    g->set_red();
    InsertFixup(g);
  }
}

template <class Key, class Value, class Compare>
void search_tree<Key, Value, Compare>::erase(iterator pos) {
  Node* u = pos.ptr_;
  Node* r;              // replacement
  auto oc = u->color_;  // original color

  if (u->left_ == nil_) {
    r = u->right_;
    TransplantSubtree(u, r);
  } else if (u->right_ == nil_) {
    r = u->left_;
    TransplantSubtree(u, r);
  } else {
    Node* r2 = u->right_;  // second replacement
    while (r2->left_ != nil_) r2 = r2->left_;

    oc = r2->color_;
    r = r2->right_;

    if (r2 == u->right_)  // nil-node case
      r->parent_ = r2;
    else {
      TransplantSubtree(r2, r);
      r2->right_ = u->right_;
      r2->right_->parent_ = r2;
    }

    TransplantSubtree(u, r2);
    r2->left_ = u->left_;
    r2->left_->parent_ = r2;
    r2->color_ = u->color_;
  }

  delete u, n_--;
  if (r == root_ || r->is_red() || oc == Node::Color::red)
    r->set_black();
  else
    EraseFixup(r);
}

template <class Key, class Value, class Compare>
void search_tree<Key, Value, Compare>::TransplantSubtree(Node* dst,
                                                         Node* src) noexcept {
  if (dst->parent_ == nil_) {
    root_ = src;
    nil_->left_ = src;
  } else if (dst->is_left())
    dst->parent_->left_ = src;
  else
    dst->parent_->right_ = src;
  src->parent_ = dst->parent_;
}

template <class Key, class Value, class Compare>
void search_tree<Key, Value, Compare>::EraseFixup(Node* node) noexcept {
  Node* u = node;
  Node* p = u->parent();
  Node* s = u->sibling();  // sibling
  if (s->is_black()) {
    if (s->left_->is_red() || s->right_->is_red()) {
      Node* n = (s->left_->is_red() ? s->left_ : s->right_);  // nephew
      auto top_color = p->color_;
      n = TrinodeRestructure(n);
      n->set_color(top_color);
      u->set_black();
      n->left_->set_black();
      n->right_->set_black();
    } else {
      u->set_black();
      s->set_red();
      if (p->is_black() && p != root_) EraseFixup(p);
      p->set_black();
    }
  } else {
    Node* n = (s->is_right() ? s->right_ : s->left_);
    n = TrinodeRestructure(n);
    u->parent_ = p;  // restore nil-node parent after restructure
    s->set_black();
    p->set_red();
    EraseFixup(u);
  }
}

template <class K, class V, class C>
typename search_tree<K, V, C>::Node* search_tree<K, V, C>::TrinodeRestructure(
    Node* node) noexcept {
  Node* n = node;
  Node* p = n->parent();
  Node* g = n->grandparent();

  Node *a, *b, *c;  // inorder naming of n, p, g
  Node *t1, *t2, *t3,
      *t4;  // inorder naming of subtrees not rooted at n, p, g
  if (g->right_ == p && p->right_ == n)
    a = g, b = p, c = n, t2 = b->left_, t3 = c->left_;
  if (g->right_ == p && p->left_ == n)
    a = g, b = n, c = p, t2 = b->left_, t3 = b->right_;
  if (g->left_ == p && p->left_ == n)
    a = n, b = p, c = g, t2 = a->right_, t3 = b->right_;
  if (g->left_ == p && p->right_ == n)
    a = p, b = n, c = g, t2 = b->left_, t3 = b->right_;

  TransplantSubtree(g, b);
  b->left_ = a, b->right_ = c, a->parent_ = c->parent_ = b;
  a->right_ = t2, t2->parent_ = a;
  c->left_ = t3, t3->parent_ = c;
  (void)t1, (void)t4;  // t1, t4 retain their initial positions

  return b;
}

template <class T1, class T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
  os << '{' << p.first << ',' << p.second << '}';
  return os;
}

template <class Key, class Value, class Compare>
void search_tree<Key, Value, Compare>::PrintRecursive(
    std::ostream& os, const std::string& prefix, Node* node,
    bool is_left) const noexcept {
  os << prefix;
  os << (is_left ? "├──" : "└──");

  if (node == nil_)
    os << "N";
  else
    os << (node->is_red() ? "R" : "B") << ":" << node->data_;
  os << std::endl;

  if (node == nil_) return;
  PrintRecursive(os, prefix + (is_left ? "│   " : "    "), node->left_, true);
  PrintRecursive(os, prefix + (is_left ? "│   " : "    "), node->right_, false);
}

// ITERATOR

template <class Key, class Value, class Compare>
template <bool is_const>
auto& search_tree<Key, Value, Compare>::Iterator<is_const>::operator++() {
  Node* nptr = ptr_->right_;
  if (nptr->is_internal()) {
    do {
      ptr_ = nptr;
      nptr = ptr_->left_;
    } while (nptr->is_internal());
  } else {
    nptr = ptr_->parent_;
    while (ptr_ == nptr->right_) {
      ptr_ = nptr;
      nptr = ptr_->parent_;
    }
    ptr_ = nptr;
  }
  return *this;
}

template <class Key, class Value, class Compare>
template <bool is_const>
auto& search_tree<Key, Value, Compare>::Iterator<is_const>::operator--() {
  Node* nptr = ptr_->left_;
  if (nptr->is_internal()) {
    do {
      ptr_ = nptr;
      nptr = ptr_->right_;
    } while (nptr->is_internal());
  } else {
    nptr = ptr_->parent_;
    while (ptr_ == nptr->left_) {
      ptr_ = nptr;
      nptr = ptr_->parent_;
    }
    ptr_ = nptr;
  }
  return *this;
}

}  // namespace s21
#endif  // search_tree_H_
