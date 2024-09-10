#ifndef _SRC_STACK_S21_STACK_H_
#define _SRC_STACK_S21_STACK_H_

#include <iostream>
#include <stack>
#include <string>

#include "../vector/s21_vector.h"

namespace s21 {

template <class T, class Container = vector<T>>
class stack {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  stack() : container_() {}
  stack(std::initializer_list<value_type> const &items) {
    for (auto i = items.begin(); i != items.end(); i++) push(*i);
  }
  stack(const stack &s) : container_(s.container_) {}
  stack(stack &&s) : container_(std::move(s.container_)) {}
  ~stack(){};
  stack &operator=(stack &&s) noexcept {
    this->container_ = std::move(s.container_);
    return *this;
  }

  stack &operator=(const stack &other) {
    if (this != &other) {
      this->container_ = other.container_;
    }
    return *this;
  }

  const_reference top() const { return this->container_.back(); }

  bool empty() const { return this->container_.empty(); }
  size_type size() const { return this->container_.size(); }

  void push(const_reference value) { this->container_.push_back(value); }
  void pop() { this->container_.pop_back(); }
  void swap(stack &other) { this->container_.swap(other.container_); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push(args), ...);
  };

  void print() {
    for (size_t i = 0; i < this->container_.size(); i++) {
      std::cout << this->container_[i] << " ";
    }
    std::cout << std::endl;
  }

 private:
  Container container_;
};

};  // namespace s21

#endif