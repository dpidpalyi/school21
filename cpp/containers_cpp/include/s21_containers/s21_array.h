#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <algorithm>
#include <initializer_list>

namespace s21 {

template <typename T, std::size_t S>

class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  // Member functions
 public:
  array() = default;

  array(std::initializer_list<value_type> const &items) {
    if (items.size() != S) {
      throw std::invalid_argument(
          "Error: Incorrect size of the initializer list during array "
          "initialization");
    }
    size_type i = 0;
    for (const auto &item : items) {
      data_[i++] = item;
    }
  }

  array(const array &rhs) noexcept : data_{} {
    for (size_type i = 0; i < S; ++i) {
      data_[i] = rhs.data_[i];
    }
  }

  array &operator=(const array &rhs) noexcept {
    if (this != &rhs) {
      for (size_type i = 0; i < S; ++i) {
        data_[i] = rhs.data_[i];
      }
    }
    return *this;
  }

  array(array &&rhs) noexcept {
    if (this != &rhs) {
      std::move(rhs.data_, rhs.data_ + S, data_);
    }
  }

  array &operator=(array &&rhs) noexcept {
    if (this != &rhs) {
      for (size_type i = 0; i < S; ++i) {
        data_[i] = std::move(rhs.data_[i]);
      }
    }
    return *this;
  }

  ~array() {}

  // Element access
 public:
  constexpr reference at(size_type index) {
    return (index < S)
               ? data_[index]
               : throw std::out_of_range("s21::array::at Index out of bounds");
  }

  constexpr const_reference at(size_type index) const {
    return (index < S)
               ? data_[index]
               : throw std::out_of_range("s21::array::at Index out of bounds");
  }

  constexpr reference operator[](size_type index) { return at(index); }

  constexpr const_reference operator[](size_type index) const {
    return at(index);
  }

  reference front() { return data_[0]; }

  const_reference front() const { return data_[0]; }

  reference back() { return data_[S - 1]; }

  const_reference back() const { return data_[S - 1]; }

  constexpr iterator data() noexcept { return data_; }

  constexpr const_iterator data() const noexcept { return data_; }

  // Iterators
 public:
  constexpr iterator begin() noexcept { return data_; }

  constexpr const_iterator begin() const noexcept { return data_; }

  constexpr const_iterator cbegin() const noexcept { return begin(); }

  constexpr iterator end() noexcept { return data_ + S; }

  constexpr const_iterator end() const noexcept { return data_ + S; }

  constexpr const_iterator cend() const noexcept { return end(); }

  // Capacity
 public:
  [[nodiscard]] constexpr size_type size() const noexcept {
    return std::distance(begin(), end());
  }

  [[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }

  [[nodiscard]] constexpr size_type max_size() const noexcept { return S; }

  // Modifiers
 public:
  constexpr void swap(array &other) noexcept {
    for (std::size_t i = 0; i < S; ++i) {
      T temp = std::move(data_[i]);
      data_[i] = std::move(other.data_[i]);
      other.data_[i] = std::move(temp);
    }
  }

  void fill(const T &value) {
    for (size_t i = 0; i < S; ++i) {
      data_[i] = value;
    }
  }

 private:
  value_type data_[S] = {};
};

}  // namespace s21

#endif  // S21_ARRAY_H_
