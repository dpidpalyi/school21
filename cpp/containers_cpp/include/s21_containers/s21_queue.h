#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "s21_list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;
  using container_type = Container;

  queue() = default;

  queue(std::initializer_list<value_type> const &items) : c{items} {}

  queue(const queue &other) : c(other.c) {}

  queue(queue &&other) noexcept : c(std::move(other.c)) {}

  queue &operator=(const queue &other) {
    c = other.c;
    return *this;
  }

  queue &operator=(queue &&other) noexcept {
    c = std::move(other.c);
    return *this;
  }

  ~queue() = default;

  reference front() { return c.front(); };

  reference back() { return c.back(); }

  const_reference front() const { return c.front(); }

  const_reference back() const { return c.back(); }

  bool empty() const noexcept { return c.empty(); }

  size_type size() const noexcept { return c.size(); }

  void push(const_reference value) { c.push_back(value); }

  void pop() { c.pop_front(); }

  void swap(queue &other) noexcept {
    using std::swap;
    swap(c, other.c);
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    return (c.insert_many_back(args...));
  }

 protected:
  // The underlying container
  Container c;
};

}  // namespace s21

#endif  // S21_QUEUE_H_
