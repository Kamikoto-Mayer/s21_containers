#ifndef _SRC_VECTOR_S21_VECTOR_H_
#define _SRC_VECTOR_S21_VECTOR_H_

#include <iostream>
#include <string>
#include <vector>

namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&other) noexcept;
  ~vector();
  vector &operator=(const vector &other);
  vector &operator=(vector &&other) noexcept;
  reference at(size_type pos);
  reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator data();
  const_iterator data() const;
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  void print();

 private:
  size_type size_;
  size_type capacity_;
  value_type *container_;
  void conversion_to_zero();
};
};  // namespace s21
#include "s21_vector.tpp"
#endif