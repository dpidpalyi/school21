#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <utility>

namespace s21 {

template <typename T>
class list {
 private:
  struct Node;

 public:
  struct ListIterator;
  struct ListConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using pointer = T *;
  using const_pointer = const T *;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  struct ListIterator {
    ListIterator(Node *p = nullptr) : ptr(p) {}

    reference operator*() const { return ptr->data; }

    pointer operator->() const { return &**this; }

    ListIterator &operator++() {
      ptr = ptr->next;
      return *this;
    }

    ListIterator operator++(int) {
      auto ret = *this;
      ++*this;
      return ret;
    }

    ListIterator &operator--() {
      ptr = ptr->prev;
      return *this;
    }

    ListIterator operator--(int) {
      auto ret = *this;
      --*this;
      return ret;
    }

    bool operator==(const ListIterator &other) const {
      return ptr == other.ptr;
    }

    bool operator!=(const ListIterator &other) const {
      return !(*this == other);
    }

    operator ListConstIterator() const { return ListConstIterator(ptr); }

   private:
    friend class list<value_type>;
    friend struct ListConstIterator;
    Node *ptr;
  };

  struct ListConstIterator : public ListIterator {
    using ListIterator::ListIterator;
    const_reference operator*() const { return ListIterator::operator*(); }

    const_pointer operator->() const { return ListIterator::operator->(); }
  };

  list() {
    tail = new Node();
    tail->prev = tail->next = tail;
    head = tail;
  }

  explicit list(size_type count) : list() {
    while (count--) push_back(value_type());
  }

  list(std::initializer_list<value_type> const &items) : list() {
    for (const auto &e : items) push_back(e);
  }

  list(const list &other) : list() {
    for (const auto &e : other) push_back(e);
  }

  list(list &&other) noexcept
      : head(other.head), tail(other.tail), size_(other.size_) {
    other.head = other.tail = nullptr;
    other.size_ = 0;
  }

  list &operator=(const list &other) {
    if (this != &other) {
      clear();
      for (const auto &e : other) push_back(e);
    }
    return *this;
  }

  list &operator=(list &&other) noexcept {
    if (this != &other) {
      free();
      head = other.head;
      tail = other.tail;
      size_ = other.size_;
      other.head = other.tail = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  ~list() { free(); }

  reference front() { return *begin(); }

  reference back() { return *--end(); }

  const_reference front() const { return *begin(); }

  const_reference back() const { return *--end(); }

  iterator begin() noexcept { return iterator(head); }

  iterator end() noexcept { return iterator(tail); }

  const_iterator begin() const noexcept { return const_iterator(head); }

  const_iterator end() const noexcept { return const_iterator(tail); }

  const_iterator cbegin() const noexcept { return begin(); }

  const_iterator cend() const noexcept { return end(); }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept { return SIZE_MAX / sizeof(Node) / 2; }

  iterator insert(const_iterator pos, const_reference value) {
    Node *n = new Node(value);
    n->next = pos.ptr;
    n->prev = pos.ptr->prev;
    n->prev->next = pos.ptr->prev = n;
    if (head == pos.ptr) head = n;
    ++size_;
    return n;
  }

  iterator erase(const_iterator pos) {
    auto popped = pos.ptr;
    auto ret = popped->next;
    popped->prev->next = popped->next;
    popped->next->prev = popped->prev;
    --size_;
    if (head == popped) head = popped->next;
    delete popped;
    return ret;
  }

  void push_back(const_reference value) { insert(cend(), value); }

  void pop_back() { erase(--cend()); }

  void push_front(const_reference value) { insert(cbegin(), value); }

  void pop_front() { erase(cbegin()); }

  void swap(list &other) noexcept {
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(size_, other.size_);
  }

  void merge(list &other) {
    if (this == &other) return;
    auto curr = head;
    auto other_curr = other.head;
    auto temp = curr;
    while (other_curr != other.tail) {
      if (curr == tail) {
        splice(end(), other);
        return;
      }
      if (!(curr->data < other_curr->data)) {
        temp = other_curr->next;
        temp->prev = other.tail;
        curr->prev->next = other_curr;
        other_curr->prev = curr->prev;
        curr->prev = other_curr;
        other_curr->next = curr;
        if (curr == head) head = other_curr;
        other_curr = temp;
      } else
        curr = curr->next;
    }
    other.head = other.tail;
    other.tail->prev = other.tail->next = tail;
    size_ += other.size();
    other.size_ = 0;
  }

  void splice(const_iterator pos, list &other) {
    if (!other.empty()) {
      auto p = pos.ptr;
      auto b = other.begin().ptr;
      auto e = other.end().ptr;
      p->prev->next = b;
      b->prev = p->prev;
      e->prev->next = p;
      p->prev = e->prev;
      head = tail->next;
      other.head = other.tail;
      other.tail->prev = other.tail->next = tail;
      size_ += other.size();
      other.size_ = 0;
    }
  }

  void reverse() noexcept {
    using std::swap;
    auto curr = head;
    while (curr != tail) {
      swap(curr->next, curr->prev);
      curr = curr->prev;
    }
    swap(tail->next, tail->prev);
    head = tail->next;
  }

  void unique() {
    for (auto curr = begin(), prev = begin(); curr != end(); curr = prev)
      if (*++curr == *prev)
        erase(curr);
      else
        ++prev;
  }

  void sort() {
    if (size() > 1) {
      QuickSort(head, tail->prev);
      head = tail->next;
    }
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    for (auto &&item : {std::forward<Args>(args)...}) insert(pos, item);
    return --pos;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(cend(), args...);
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    insert_many(cbegin(), args...);
  }

 private:
  struct Node {
    Node() = default;
    explicit Node(const_reference value) : data(value) {}

    Node *next{nullptr};
    Node *prev{nullptr};
    value_type data;
  };

  void clear() noexcept {
    while (head != tail) pop_back();
  }

  void free() {
    clear();
    delete tail;
  }

  void swap(Node &left, Node &right) {
    using std::swap;
    if (&left == &right) return;
    left.prev->next = &right;
    right.next->prev = &left;
    if (&left != right.prev) {
      left.next->prev = &right;
      right.prev->next = &left;
      swap(left.next, right.next);
      swap(left.prev, right.prev);
    } else {
      swap(left.next, left.prev);
      swap(right.next, right.prev);
      swap(left.next, right.prev);
    }
  }

  void QuickSort(Node *first, Node *last) {
    // Store ptrs to restore index, cause we move pointers through list
    Node *first_cpy = first->prev;
    Node *last_cpy = last->next;

    // if (last != tail && first != last && first != last->next) {
    if (first != last && first != last->next) {
      Node *p = partition(first_cpy->next, last_cpy->prev);
      QuickSort(first_cpy->next, p->prev);
      QuickSort(p->next, last_cpy->prev);
    }
  }

  Node *partition(Node *first, Node *last) {
    value_type pivot = last->data;
    Node *slow = first->prev;

    for (Node *fast = first; fast != last; fast = fast->next) {
      if (!(pivot < fast->data)) {
        slow = slow->next;
        swap(*slow, *fast);
        // Need to restore index, cause we change links
        std::swap(slow, fast);
      }
    }
    slow = slow->next;
    swap(*slow, *last);

    return last;
  }

  // Private members
  Node *head{nullptr};
  Node *tail{nullptr};
  size_type size_{0};
};

}  // namespace s21

#endif  // S21_LIST_H_
