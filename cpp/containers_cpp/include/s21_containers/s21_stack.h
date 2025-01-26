#ifndef S21_STACK_H
#define S21_STACK_H

#include "s21_list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class stack {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;
  using container_type = Container;

  stack() = default;

  stack(std::initializer_list<value_type> const &items) : c{items} {}

  stack(const stack &other) : c(other.c) {}

  stack(stack &&other) noexcept : c(std::move(other.c)) {}

  stack &operator=(const stack &other) {
    c = other.c;
    return *this;
  }

  stack &operator=(stack &&other) noexcept {
    c = std::move(other.c);
    return *this;
  }

  ~stack() = default;

  reference top() { return c.back(); };

  const_reference top() const { return c.back(); }

  bool empty() const noexcept { return c.empty(); }

  size_type size() const noexcept { return c.size(); }

  void push(const_reference value) { c.push_back(value); }

  void pop() { c.pop_back(); }

  void swap(stack &other) noexcept {
    using std::swap;
    swap(c, other.c);
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    return (c.insert_many_front(args...));
  }

 protected:
  // The underlying container
  Container c;
};

}  // namespace s21

#endif  // S21_QUEUE_H_
