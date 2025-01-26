#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  // Member functions
 public:
  vector() : size_(0), capacity_(0), data_(nullptr) {}

  explicit vector(size_type n) {
    size_ = n;
    capacity_ = n;
    data_ = nullptr;
    if (n > 0) {
      data_ = new value_type[capacity_];
    }
  }

  explicit vector(std::initializer_list<value_type> const &items)
      : size_{items.size()},
        capacity_(items.size()),
        data_{new value_type[capacity_]} {
    std::copy(items.begin(), items.end(), data_);
  }

  vector(const vector &v)
      : size_{v.size_},
        capacity_{v.capacity_},
        data_{new value_type[capacity_]} {
    if (data_ != nullptr) {
      std::copy(v.data_, v.data_ + v.size_, data_);
    }
  }

  vector(vector &&v) noexcept
      : size_{std::exchange(v.size_, 0)},
        capacity_{std::exchange(v.capacity_, 0)},
        data_{std::exchange(v.data_, nullptr)} {}

  ~vector() { delete[] data_; }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] data_;

      size_ = std::exchange(v.size_, 0);
      capacity_ = std::exchange(v.capacity_, 0);
      data_ = std::exchange(v.data_, nullptr);
    }

    return *this;
  }

  vector &operator=(const vector &rhs) {
    if (this != &rhs) {
      delete[] data_;

      if (rhs.size_ > 0) {
        data_ = new value_type[rhs.size_];
        if (data_ != nullptr) {
          std::copy(rhs.data_, rhs.data_ + rhs.size_, data_);
        }
      } else {
        data_ = nullptr;
      }
      size_ = rhs.size_;
      capacity_ = rhs.size_;
    }
    return *this;
  }

  // Element Access
 public:
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference operator[](size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return data_[pos];
  }

  reference front() {
    if (size_ == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return data_[0];
  }

  const_reference front() const {
    if (size_ == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return data_[0];
  }

  reference back() {
    if (size_ == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return data_[size_ - 1];
  }

  const_reference back() const {
    if (size_ == 0) {
      throw std::out_of_range("Vector is empty");
    }
    return data_[size_ - 1];
  }

  iterator data() noexcept { return data_; }

  const_iterator data() const noexcept { return data_; }

  // Vector Iterators
 public:
  iterator begin() noexcept { return data_; }

  const_iterator begin() const noexcept { return data_; }

  const_iterator cbegin() const noexcept { return begin(); }

  iterator end() noexcept { return data_ + size_; }

  const_iterator end() const noexcept { return data_ + size_; }

  const_iterator cend() const noexcept { return end(); }

  // Vector Capacity
 public:
  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }

  void reserve(size_type new_capacity) {
    if (new_capacity > capacity_) {
      T *new_data = new T[new_capacity];
      std::copy(data_, data_ + size_, new_data);
      delete[] data_;
      data_ = new_data;
      capacity_ = new_capacity;
    }
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      T *new_data = new T[size_];
      std::copy(data_, data_ + size_, new_data);
      delete[] data_;
      data_ = new_data;
      capacity_ = size_;
    }
  }

  void clear() noexcept {
    if (data_ != nullptr) {
      delete[] data_;
      data_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }

  iterator insert(iterator pos, const_reference value) {
    size_type index = static_cast<size_type>(pos - begin());

    if (index > size_) {
      throw std::out_of_range("Out of range");
    }

    if (size_ == capacity_) {
      reserve((capacity_ == 0) ? 1 : 2 * capacity_);
    }

    value_type tmp = value;

    for (size_t i = size_; i > index; --i) {
      *(data_ + i) = *(data_ + i - 1);
    }

    *(data_ + index) = tmp;
    ++size_;

    return begin() + index;
  }

  void erase(iterator pos) {
    size_type index = pos - data_;
    if (index < size_) {
      std::copy(data_ + index + 1, data_ + size_, data_ + index);
      --size_;
    } else {
      throw std::out_of_range("Out of range");
    }
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve((capacity_ == 0) ? 1 : 2 * capacity_);
    }

    data_[size_] = value;
    ++size_;
  }

  void push_back(value_type &&value) {
    if (size_ == capacity_) {
      reserve((capacity_ == 0) ? 1 : 2 * capacity_);
    }

    data_[size_] = std::move(value);
    ++size_;
  }

  void pop_back() {
    if (size_ > 0) {
      --size_;
    }
  }

  void swap(vector &other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    size_type index = pos - data_;

    size_type num_elements = sizeof...(args);

    if (size_ + num_elements > capacity_) {
      reserve(std::max(2 * capacity_, size_ + num_elements));
    }

    std::copy_backward(data_ + index, data_ + size_,
                       data_ + size_ + num_elements);

    ((data_[index++] = std::forward<Args>(args)), ...);
    size_ += num_elements;

    return data_ + index - num_elements;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    size_type num_elements = sizeof...(args);

    if (size_ + num_elements > capacity_) {
      reserve(std::max(2 * capacity_, size_ + num_elements));
    }

    ((data_[size_++] = std::forward<Args>(args)), ...);
  }

 private:
  size_type size_ = 0;
  size_type capacity_ = 0;
  iterator data_ = nullptr;
};

}  // namespace s21

#endif  // S21_VECTOR_H_
