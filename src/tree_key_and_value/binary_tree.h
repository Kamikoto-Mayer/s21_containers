#ifndef _SRC_TREE_KEY_AND_VALUE_BINARY_TREE_H_
#define _SRC_TREE_KEY_AND_VALUE_BINARY_TREE_H_

#include <iostream>
#include <limits>

namespace s21 {

template <typename K, typename V>
struct Node_ {
 public:
  using val_k_t = std::pair<K, V>;
  Node_ *Left;
  Node_ *Right;
  Node_ *Parent;
  val_k_t Key;
  Node_() : Left(nullptr), Right(nullptr), Key(), Parent(nullptr){};
  Node_(const val_k_t &data) : Left(nullptr), Right(nullptr), Parent(nullptr) {
    Key = data;
  };
};

template <typename K, typename V>
class Iterator_ {
 public:
  using val_k_t = std::pair<K, V>;
  Node_<K, V> *iter;
  Node_<K, V> *min_node;
  Node_<K, V> *max_node;
  Iterator_();
  Iterator_(Node_<K, V> *it);
  Iterator_ operator++();
  Iterator_ operator++(int);
  Iterator_ operator--();
  Iterator_ operator--(int);
  bool operator!=(const Iterator_ &other);
  bool operator==(const Iterator_ &other);
  val_k_t &operator*();
};

template <typename K, typename V>
class Tree {
  using val_k_t = std::pair<K, V>;
  Node_<K, V> *root;
  size_t size_;
  void pos_swap(Iterator_<K, V> &pos, Iterator_<K, V> &it);
  void suc_insert(Iterator_<K, V> &iter, const std::pair<K, V> &value);
  std::pair<Iterator_<K, V>, bool> key_check(const K &key);

 public:
  Tree();
  Tree(std::initializer_list<val_k_t> const &items);
  Tree(Tree &&m);
  Tree(const Tree &m);
  ~Tree();
  Tree &operator=(Tree &&m);
  std::pair<Iterator_<K, V>, bool> insert(const std::pair<K, V> &value);
  std::pair<Iterator_<K, V>, bool> insert_or_assign(const K &key, const V &obj);
  bool empty();
  size_t size();
  size_t max_size();
  void clear();
  Iterator_<K, V> begin();
  Iterator_<K, V> end();
  V &at(const K &key);
  V &operator[](const K &key);
  void erase(Iterator_<K, V> pos);
  bool contains(const K &key);
};

}  // namespace s21

#include "binary_tree.tpp"
#endif
