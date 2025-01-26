#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <vector>

#include "detail/s21_rbtree.h"

namespace s21 {

template <class Key, class T, class Compare = std::less<Key>>
class map {
  using tree_type = search_tree<Key, T, Compare>;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;
  using size_type = size_t;
  using reverse_iterator = typename tree_type::reverse_iterator;
  using const_reverse_iterator = typename tree_type::const_reverse_iterator;

  // special
  map() = default;
  map(std::initializer_list<value_type> const &items) {
    for (auto &&elem : items) tree_.insert_if_ne(elem);
  }
  map(const map &other) : tree_(other.tree_) {}
  map &operator=(const map &other) {
    if (this != &other) tree_.operator=(other.tree_);
    return *this;
  }
  map(map &&other) noexcept : tree_(std::move(other.tree_)) {}
  map &operator=(map &&other) noexcept {
    if (this != &other) tree_.operator=(std::move(other.tree_));
    return *this;
  }
  ~map() = default;

  // comparison
  friend bool operator==(const map &a, const map &b) {
    return operator==(a.tree_, b.tree_);
  }
  friend bool operator!=(const map &a, const map &b) {
    return operator!=(a.tree_, b.tree_);
  }

  // iterators
  iterator begin() noexcept { return tree_.begin(); }
  iterator end() noexcept { return tree_.end(); }
  const_iterator begin() const noexcept { return tree_.begin(); }
  const_iterator end() const noexcept { return tree_.end(); }
  const_iterator cbegin() const noexcept { return tree_.cbegin(); }
  const_iterator cend() const noexcept { return tree_.cend(); }
  reverse_iterator rbegin() noexcept { return tree_.rbegin(); }
  reverse_iterator rend() noexcept { return tree_.rend(); }
  const_reverse_iterator rbegin() const noexcept { return tree_.rbegin(); }
  const_reverse_iterator rend() const noexcept { return tree_.rend(); }
  const_reverse_iterator crbegin() const noexcept { return tree_.crbegin(); }
  const_reverse_iterator crend() const noexcept { return tree_.crend(); }

  // element access
  const T &at(const Key &key) const { return tree_.at(key); }
  T &at(const Key &key) { return tree_.at(key); }
  T &operator[](const Key &key) { return tree_[key]; }

  // capacity
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept { return tree_.max_size(); }
  [[nodiscard]] bool empty() const noexcept { return tree_.empty(); }

  // modifiers
  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_.insert_if_ne(value);
  }
  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return tree_.insert_if_ne(key, obj);
  }
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    return tree_.insert_or_assign(key, obj);
  }
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return tree_.insert_if_ne_many(std::forward<Args>(args)...);
  }
  void erase(const Key &key) noexcept { tree_.erase(key); }
  void erase(iterator pos) noexcept { tree_.erase(pos); }
  void clear() noexcept { tree_.clear(); }
  void merge(map &other) { tree_.merge_if_ne(other.tree_); }
  void swap(map &other) noexcept { tree_.swap(other.tree_); }

  // lookup
  bool contains(const Key &key) const noexcept { return tree_.contains(key); }
  iterator find(const Key &key) noexcept { return tree_.find(key); }
  const_iterator find(const Key &key) const noexcept { return tree_.find(key); }

 private:
  tree_type tree_;
};

}  // namespace s21
#endif  // S21_MAP_H_
