#ifndef _SRC_MAP_S21_MAP_H_
#define _SRC_MAP_S21_MAP_H_

#include <vector>

#include "../tree_key_and_value/binary_tree.h"
namespace s21 {

template <typename Key, typename T>
class map : public Tree<Key, T> {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  // using const_iterator = MapConstIterator<Key, T>;
  using size_type = size_t;

 public:
  using iterator = Iterator_<Key, T>;
  map() : Tree<key_type, mapped_type>(){};
  map(std::initializer_list<value_type> const& items);
  map(const map& m) : Tree<key_type, mapped_type>(m){};
  map(map&& m) : Tree<key_type, mapped_type>(std::move(m)){};
  map& operator=(map&& m);

  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void swap(map& other);
  void merge(map& other);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};
}  // namespace s21

#include "s21_map.tpp"
#endif