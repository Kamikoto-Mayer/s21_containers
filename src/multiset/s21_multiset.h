#ifndef _SRC_MULTISET_S21_MULTISET_H_
#define _SRC_MULTISET_S21_MULTISET_H_

#include "../set/s21_set.h"

namespace s21 {
template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator<Key>;
  using const_iterator = ConstIterator<Key>;
  using size_type = size_t;

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset();
  multiset& operator=(multiset&& ms);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);
  size_type count(const Key& key);
  iterator find(const Key& key);
  bool contains(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  set<Key> set_;
  void suc_insert(iterator& iter, const key_type& value);
  std::pair<iterator, bool> insert(const value_type& value, int);
};
}  // namespace s21

#include "s21_multiset.tpp"
#endif