#ifndef _SRC_LIST_S21_LIST_H_
#define _SRC_LIST_S21_LIST_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  struct Node {
   public:
    Node *next_;
    Node *prev_;
    value_type value_;
    Node(const value_type &value) : value_(value) {
      prev_ = nullptr;
      next_ = nullptr;
    }
  };

  Node *head_;
  Node *tail_;
  size_t size_;

 public:
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list &operator=(list &&l);
  list &operator=(const list &other);
  const_reference front();
  const_reference back();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void reverse();
  void unique();
  void sort();

  class ListIterator {
   public:
    Node *ptr_;
    list *eage;
    ListIterator();
    ListIterator(list &ptr);
    reference operator*();
    ListIterator &operator++();
    ListIterator operator++(int);
    ListIterator &operator--();
    ListIterator operator--(int);
    bool operator==(const ListIterator &other);
    bool operator!=(const ListIterator &other);
  };

  using iterator = ListIterator;

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator(ListIterator other) : ListIterator(other){};
    const value_type &operator*() { return ListIterator::operator*(); }
  };

  using const_iterator = ListConstIterator;

  iterator begin();
  iterator end();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void splice(const_iterator pos, list &other);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);
};
}  // namespace s21

#include "s21_list.tpp"

#endif