template <class Key>
s21::multiset<Key>::multiset() : set_(){};

template <class Key>
s21::multiset<Key>::multiset(const std::initializer_list<Key> &items)
    : multiset() {
  for (auto el : items) {
    insert(el);
  }
}

template <class Key>
s21::multiset<Key>::multiset(const s21::multiset<Key> &ms) {
  const_iterator pos = ms.set_.GetConstRoot();
  while (pos.iter) {
    insert(pos.iter->K);
    ++pos;
  }
  pos = ms.set_.GetConstRoot();
  --pos;
  while (pos.iter) {
    insert(pos.iter->K);
    --pos;
  }
}

template <class Key>
s21::multiset<Key>::multiset(s21::multiset<Key> &&ms) {
  *this = std::move(ms);
}

template <class Key>
s21::multiset<Key>::~multiset() {
  clear();
}

template <class Key>
s21::multiset<Key> &s21::multiset<Key>::operator=(s21::multiset<Key> &&ms) {
  if (this != &ms) {
    clear();
    set_.SetRoot(ms.set_.GetRoot());
    set_.SetSize(ms.set_.GetSize());
    ms.set_.SetRoot(nullptr);
    ms.set_.SetSize(0);
  }
  return *this;
}

template <class Key>
s21::Iterator<Key> s21::multiset<Key>::begin() {
  return set_.begin();
}

template <class Key>
s21::Iterator<Key> s21::multiset<Key>::end() {
  return set_.end();
}

template <class Key>
s21::Iterator<Key> s21::multiset<Key>::insert(const Key &value) {
  iterator iter = set_.GetRoot();
  if (!set_.GetSize()) {
    Node<Key> *current = new Node<Key>(value);
    iter.iter = current;
    set_.SetRoot(iter.iter);
    set_.SetSize((set_.GetSize() + 1));
  } else {
    suc_insert(iter, value);
  }
  return iter;
}

template <class Key>
void s21::multiset<Key>::suc_insert(s21::Iterator<Key> &iter,
                                    const Key &value) {
  iterator Parent;
  bool b = true;
  Node<Key> *current = new Node<Key>(value);
  while (b) {
    if (iter.iter->K > value) {
      if (iter.iter->Left == nullptr) {
        iter.iter->Left = current;
        iter.iter->Left->Parent = iter.iter;
        b = false;
      } else {
        Parent = iter;
        iter = iter.iter->Left;
      }
    } else if (iter.iter->K <= value) {
      if (iter.iter->Right == nullptr) {
        iter.iter->Right = current;
        iter.iter->Right->Parent = iter.iter;
        b = false;
      } else {
        Parent = iter;
        iter = iter.iter->Right;
      }
    }
  }
  iter = current;
  set_.SetSize((set_.GetSize() + 1));
}

template <class Key>
void s21::multiset<Key>::clear() {
  set_.clear();
}

template <class Key>
void s21::multiset<Key>::erase(s21::Iterator<Key> pos) {
  set_.erase(pos);
}

template <class Key>
bool s21::multiset<Key>::empty() {
  return set_.empty();
}

template <class Key>
size_t s21::multiset<Key>::size() {
  return set_.size();
}

template <class Key>
size_t s21::multiset<Key>::max_size() {
  return set_.max_size();
}

template <class Key>
void s21::multiset<Key>::swap(s21::multiset<Key> &other) {
  multiset<Key> tmp = *this;
  *this = std::move(other);
  other = std::move(tmp);
}

template <class Key>
s21::Iterator<Key> s21::multiset<Key>::find(const Key &key) {
  return set_.find(key);
}

template <class Key>
bool s21::multiset<Key>::contains(const Key &key) {
  return set_.contains(key);
}

template <class Key>
void s21::multiset<Key>::merge(s21::multiset<Key> &other) {
  iterator pos = other.set_.begin();
  while (pos.iter) {
    insert(*pos);
    other.erase(pos);
    ++pos;
  }
}

template <class Key>
size_t s21::multiset<Key>::count(const Key &key) {
  iterator pos = set_.begin();
  size_type repit = 0;
  while (pos.iter) {
    if (*pos == key) ++repit;
    ++pos;
  }
  return repit;
}

template <class Key>
std::pair<s21::Iterator<Key>, s21::Iterator<Key>>
s21::multiset<Key>::equal_range(const Key &key) {
  iterator pos_eq = find(key);
  iterator pos_range = find(key);
  while (*pos_range == key) {
    ++pos_range;
  }
  return std::pair<iterator, iterator>(pos_eq, pos_range);
}

template <class Key>
s21::Iterator<Key> s21::multiset<Key>::upper_bound(const Key &key) {
  iterator pos = set_.begin();
  while (*pos <= key) {
    ++pos;
  }
  return pos;
}

template <class Key>
s21::Iterator<Key> s21::multiset<Key>::lower_bound(const Key &key) {
  iterator pos = set_.begin();
  while (*pos < key) {
    ++pos;
  }
  return pos;
}

template <class Key>
template <class... Args>
std::vector<std::pair<s21::Iterator<Key>, bool>>
s21::multiset<Key>::insert_many(Args &&...args) {
  std::vector<std::pair<s21::Iterator<Key>, bool>> res;
  (res.push_back(insert(args, 1)), ...);
  return res;
}

template <class Key>
std::pair<s21::Iterator<Key>, bool> s21::multiset<Key>::insert(const Key &value,
                                                               int) {
  return std::pair<s21::Iterator<Key>, bool>(insert(value), true);
}