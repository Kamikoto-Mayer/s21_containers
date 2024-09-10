#ifndef _SRC_SET_S21_SET_H_
#define _SRC_SET_S21_SET_H_

#include <iostream>
#include <limits>
#include <vector>

namespace s21 {
template <typename Key>
struct Node {
 public:
  Node *Left;
  Node *Right;
  Node *Parent;
  Key K;
  Node() : Left(nullptr), Right(nullptr), K(), Parent(nullptr){};
  Node(const Key &data) : Left(nullptr), Right(nullptr), Parent(nullptr) {
    K = data;
  };
};

template <typename Key>
class Iterator {
 public:
  Node<Key> *iter;
  Node<Key> *min_node;
  Node<Key> *max_node;
  Iterator();
  Iterator(Node<Key> *it);
  Iterator operator++();
  Iterator operator++(int);
  Iterator operator--();
  Iterator operator--(int);
  bool operator!=(const Iterator &other);
  bool operator==(const Iterator &other);
  Key &operator*();
};

template <typename Key>
class ConstIterator {
 public:
  const Node<Key> *iter;
  const Node<Key> *min_node;
  const Node<Key> *max_node;
  ConstIterator();
  ConstIterator(const Node<Key> *it);
  ConstIterator operator++();
  ConstIterator operator++(int);
  ConstIterator operator--();
  ConstIterator operator--(int);
  bool operator!=(const ConstIterator &other);
  bool operator==(const ConstIterator &other);
  const Key &operator*();
};

template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator<Key>;
  using const_iterator = ConstIterator<Key>;
  using size_type = size_t;

 private:
  Node<key_type> *root;
  size_type size_;
  void pos_swap(iterator &pos, iterator &it);
  void suc_insert(iterator &iter, const key_type &value);
  std::pair<iterator, bool> key_check(const key_type &key);

 public:
  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set();
  set &operator=(set &&s);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);
  iterator find(const Key &key);
  bool contains(const Key &key);
  void SetSize(size_type val);
  size_type GetSize();
  void SetRoot(Node<key_type> *val);
  s21::Node<Key> *GetRoot();
  const s21::Node<Key> *GetConstRoot() const;
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

}  // namespace s21

#include "s21_set.tpp"

#endif
