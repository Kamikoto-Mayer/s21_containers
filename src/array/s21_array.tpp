#ifndef _SCR_ARRAY_ARRAY_TPP_
#define _SCR_ARRAY_ARRAY_TPP_

#include <algorithm>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  array() : m_arr(new value_type[N]) {}

  array(std::initializer_list<value_type> const& items) : array() {
    size_t i = 0;
    for (auto iter = items.begin(); iter != items.end(); ++iter, i++) {
      this->m_arr[i] = *iter;
    }
  }

  array(const array& a) : array() {
    for (size_t i = 0; i < this->m_size; i++) {
      this->m_arr[i] = a.m_arr[i];
    }
  }

  array(array&& a) {
    this->m_arr = a.m_arr;
    a.m_arr = nullptr;
    a.m_size = 0;
  }

  ~array() {
    delete[] this->m_arr;
    this->m_size = 0;
    this->m_arr = nullptr;
  }

  array& operator=(array&& other) noexcept {
    if (this != &other) {
      delete[] m_arr;
      m_arr = other.m_arr;
      other.m_arr = nullptr;
    }
    return *this;
  }

  iterator begin() {
    if (this->m_size == 0) {
      throw std::runtime_error("Array has no elements");
    }
    return &this->m_arr[0];
  }

  iterator end() {
    if (this->m_size == 0) {
      throw std::runtime_error("Array has no elements");
    }
    return &this->m_arr[this->m_size];
  }

  size_type size() const { return m_size; }

  size_type max_size() const { return m_size; }

  bool empty() const { return N == 0; }

  reference at(size_type pos) {
    if (pos >= this->m_size) {
      throw std::out_of_range("Argument pos must be less than size");
    }
    return this->m_arr[pos];
  }

  reference operator[](size_type pos) { return this->m_arr[pos]; }

  const_reference front() {
    if (!m_size) {
      throw std::out_of_range("empty container (in function vector::front)");
    }
    return m_arr[0];
  }

  const_reference back() {
    if (!m_size) {
      throw std::out_of_range("empty container (in function vector::back)");
    }
    return m_arr[m_size - 1];
  }

  value_type* data() { return m_arr; }

  void swap(array& other) { std::swap(this->m_arr, other.m_arr); }

  void fill(const_reference value) {
    for (size_t i = 0; i < this->m_size; i++) {
      this->m_arr[i] = value;
    }
  }

 private:
  value_type* m_arr;
  size_type m_size = N;
};
}  // namespace s21

#endif