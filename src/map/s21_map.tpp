namespace s21 {
template <typename key_type, typename mapped_type>
std::pair<s21::Iterator_<key_type, mapped_type>, bool>
s21::map<key_type, mapped_type>::insert(
    const std::pair<const key_type, mapped_type> &value) {
  return Tree<key_type, mapped_type>::insert(
      std::pair<key_type, mapped_type>(value.first, value.second));
}

template <typename key_type, typename mapped_type>
std::pair<s21::Iterator_<key_type, mapped_type>, bool>
s21::map<key_type, mapped_type>::insert(const key_type &key,
                                        const mapped_type &obj) {
  return insert(std::pair<key_type, mapped_type>(key, obj));
}

template <typename Key, typename T>
std::pair<s21::Iterator_<Key, T>, bool> s21::map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  return Tree<key_type, mapped_type>::insert_or_assign(key, obj);
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(
    const std::initializer_list<std::pair<const key_type, mapped_type>>
        &items) {
  for (const auto &el : items) {
    (*this).insert(el);
  }
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type> &map<key_type, mapped_type>::operator=(
    map<key_type, mapped_type> &&m) {
  if (this != &m) {
    Tree<key_type, mapped_type>::operator=(std::move(m));
  }
  return *this;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map<key_type, mapped_type> &other) {
  map<key_type, mapped_type> tmp = *this;
  *this = std::move(other);
  other = std::move(tmp);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::merge(map<key_type, mapped_type> &other) {
  iterator pos = other.begin();
  std::pair<iterator, bool> succses;
  while (pos.iter) {
    succses = this->insert(pos.iter->Key);
    if (!succses.second) {
      other.erase(pos);
    }
    ++pos;
  }
}

template <class Key, class T>
template <class... Args>
std::vector<std::pair<s21::Iterator_<Key, T>, bool>>
s21::map<Key, T>::insert_many(Args &&...args) {
  std::vector<std::pair<s21::Iterator_<Key, T>, bool>> results;
  (results.push_back(insert(args)), ...);
  return results;
}
}  // namespace s21