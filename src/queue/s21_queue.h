#ifndef _SRC_QUEUE_S21_QUEUE_H_
#define _SRC_QUEUE_S21_QUEUE_H_

#include <initializer_list>
#include <iostream>
#include <list>
#include <string>

#include "../list/s21_list.h"

namespace s21 {

template <class T, class Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using size_type = size_t;
  using reference = T &;
  using const_reference = const T &;

  queue();
  queue(std::initializer_list<T> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue &operator=(const queue &other);
  queue &operator=(queue &&q);
  const_reference front();
  const_reference back();
  bool empty();
  size_type size();
  void push(const_reference value);
  void pop();
  void swap(queue &other);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Container container_;
};
}  // namespace s21

#include "s21_queue.tpp"

#endif
