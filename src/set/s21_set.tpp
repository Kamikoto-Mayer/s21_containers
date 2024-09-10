template <typename Key>
s21::Iterator<Key>::Iterator()
    : iter(nullptr), min_node(nullptr), max_node(nullptr){};

template <class Key>
s21::Iterator<Key>::Iterator(s21::Node<Key> *it) {
  iter = it;
  min_node = iter;
  while (min_node && min_node->Left) {
    min_node = min_node->Left;
  }
  max_node = iter;
  while (max_node && max_node->Right) {
    max_node = max_node->Right;
  }
}

template <class Key>
s21::Iterator<Key> s21::Iterator<Key>::operator++() {
  if (iter == nullptr) {
    iter = min_node;
  } else {
    if (!iter->Right) {
      while (iter->Parent != nullptr && iter->Parent->Right == iter) {
        iter = iter->Parent;
      }
      iter = iter->Parent;
    } else {
      iter = iter->Right;
      while (iter->Left) {
        iter = iter->Left;
      }
    }
  }
  return iter;
}

template <class Key>
s21::Iterator<Key> s21::Iterator<Key>::operator++(int) {
  Iterator prev_pos = iter;
  ++(*this);
  return prev_pos;
}

template <class Key>
s21::Iterator<Key> s21::Iterator<Key>::operator--() {
  if (iter == nullptr) {
    iter = max_node;
  } else {
    if (!iter->Left) {
      while (iter->Parent != nullptr && iter == iter->Parent->Left) {
        iter = iter->Parent;
      }
      iter = iter->Parent;
    } else {
      iter = iter->Left;
      while (iter->Right) {
        iter = iter->Right;
      }
    }
  }
  return iter;
}

template <class Key>
s21::Iterator<Key> s21::Iterator<Key>::operator--(int) {
  Iterator prev_pos = iter;
  --(*this);
  return prev_pos;
}

template <class Key>
bool s21::Iterator<Key>::operator!=(const s21::Iterator<Key> &other) {
  return iter != other.iter;
}

template <class Key>
bool s21::Iterator<Key>::operator==(const s21::Iterator<Key> &other) {
  return iter == other.iter;
}

template <class Key>
Key &s21::Iterator<Key>::operator*() {
  return this->iter->K;
}

template <class Key>
s21::ConstIterator<Key>::ConstIterator()
    : iter(nullptr), min_node(nullptr), max_node(nullptr){};

template <class Key>
s21::ConstIterator<Key>::ConstIterator(const s21::Node<Key> *it)
    : ConstIterator() {
  iter = it;
  min_node = iter;
  while (min_node && min_node->Left) {
    min_node = min_node->Left;
  }
  max_node = iter;
  while (max_node && max_node->Right) {
    max_node = max_node->Right;
  }
}

template <class Key>
s21::ConstIterator<Key> s21::ConstIterator<Key>::operator++() {
  if (iter == nullptr) {
    iter = min_node;
  } else {
    if (!iter->Right) {
      while (iter->Parent != nullptr && iter->Parent->Right == iter) {
        iter = iter->Parent;
      }
      iter = iter->Parent;
    } else {
      iter = iter->Right;
      while (iter->Left) {
        iter = iter->Left;
      }
    }
  }
  return iter;
}

template <class Key>
s21::ConstIterator<Key> s21::ConstIterator<Key>::operator++(int) {
  ConstIterator prev_pos = iter;
  ++(*this);
  return prev_pos;
}

template <class Key>
s21::ConstIterator<Key> s21::ConstIterator<Key>::operator--() {
  if (iter == nullptr) {
    iter = max_node;
  } else {
    if (!iter->Left) {
      while (iter->Parent != nullptr && iter == iter->Parent->Left) {
        iter = iter->Parent;
      }
      iter = iter->Parent;
    } else {
      iter = iter->Left;
      while (iter->Right) {
        iter = iter->Right;
      }
    }
  }
  return iter;
}

template <class Key>
s21::ConstIterator<Key> s21::ConstIterator<Key>::operator--(int) {
  ConstIterator prev_pos = iter;
  --(*this);
  return prev_pos;
}

template <class Key>
bool s21::ConstIterator<Key>::operator!=(const s21::ConstIterator<Key> &other) {
  return iter != other.iter;
}

template <class Key>
bool s21::ConstIterator<Key>::operator==(const s21::ConstIterator<Key> &other) {
  return iter == other.iter;
}

template <class Key>
const Key &s21::ConstIterator<Key>::operator*() {
  return this->iter->K;
}

template <class Key>
s21::set<Key>::set() : root(nullptr), size_(){};

template <class Key>
s21::set<Key>::set(const std::initializer_list<Key> &items) : set() {
  for (const auto &el : items) {
    insert(el);
  }
}

template <class Key>
s21::set<Key>::set(const s21::set<Key> &s) : set() {
  iterator pos = s.root;
  while (pos.iter) {
    insert(pos.iter->K);
    ++pos;
  }
  pos = s.root;
  while (pos.iter) {
    insert(pos.iter->K);
    --pos;
  }
}

template <class Key>
s21::set<Key>::set(s21::set<Key> &&s) : set() {
  *this = std::move(s);
}

template <class Key>
s21::set<Key>::~set() {
  clear();
}

template <class Key>
s21::set<Key> &s21::set<Key>::operator=(s21::set<Key> &&s) {
  if (this != &s) {
    clear();
    this->root = s.root;
    this->size_ = s.size_;
    s.root = nullptr;
    s.size_ = 0;
  }
  return *this;
}

template <class Key>
typename s21::set<Key>::iterator s21::set<Key>::begin() {
  iterator pos = root;
  if (!empty()) {
    while (pos.iter->Left) {
      pos.iter = pos.iter->Left;
    }
  }
  return pos;
}

template <class Key>
typename s21::set<Key>::iterator s21::set<Key>::end() {
  iterator pos = nullptr;
  return pos;
}

template <class Key>
bool s21::set<Key>::empty() {
  return !size_;
}

template <class Key>
size_t s21::set<Key>::size() {
  return size_;
}

template <class Key>
size_t s21::set<Key>::max_size() {
  return (std::numeric_limits<size_t>::max() / sizeof(set<Key>) / 5);
}

template <class Key>
void s21::set<Key>::clear() {
  iterator pos = begin();
  while (!empty()) {
    erase(pos);
    ++pos;
  }
}

template <class Key>
std::pair<typename s21::Iterator<Key>, bool> s21::set<Key>::insert(
    const Key &value) {
  iterator iter = this->root;
  bool succses = true;
  if (!size_) {
    Node<Key> *current = new Node<Key>(value);
    iter.iter = current;
    root = iter.iter;
    ++size_;
  } else {
    succses = contains(value);
    if (!succses) {
      suc_insert(iter, value);
    } else {
      iter = find(value);
    }
  }
  return std::pair(iter, !succses);
}

template <class Key>
void s21::set<Key>::erase(s21::set<Key>::iterator pos) {
  iterator iter_pos = pos;
  if (pos.iter == root && !root->Left && !root->Right) {
    root = nullptr;
  } else {
    if (!pos.iter->Left && !pos.iter->Right) {
      if (pos.iter == pos.iter->Parent->Left)
        pos.iter->Parent->Left = nullptr;
      else
        pos.iter->Parent->Right = nullptr;
    } else {
      if (pos.iter->Right) {
        ++iter_pos;
        pos_swap(pos, iter_pos);
      } else if (pos.iter->Left) {
        --iter_pos;
        pos_swap(pos, iter_pos);
      }
    }
    if (pos.iter == root) {
      root = iter_pos.iter;
      iter_pos.iter->Parent = nullptr;
    }
  }
  delete pos.iter;
  --size_;
}

template <class Key>
void s21::set<Key>::swap(s21::set<Key> &other) {
  set<Key> tmp = *this;
  *this = std::move(other);
  other = std::move(tmp);
}

template <class Key>
void s21::set<Key>::merge(s21::set<Key> &other) {
  iterator pos = other.begin();
  std::pair<iterator, bool> succses;
  while (pos.iter) {
    succses = this->insert(pos.iter->K);
    if (succses.second) {
      other.erase(pos);
    }
    ++pos;
  }
}

template <class Key>
bool s21::set<Key>::contains(const Key &key) {
  bool res = false;
  iterator pos = begin();
  while (pos.iter && !res) {
    if (pos.iter->K == key) {
      res = true;
    }
    ++pos;
  }
  return res;
}

template <class Key>
void s21::set<Key>::pos_swap(s21::set<Key>::iterator &pos,
                             s21::set<Key>::iterator &it) {
  if (it.iter->Parent == pos.iter) {
    it.iter->Parent = pos.iter->Parent;
    if (pos.iter->Left == it.iter) {
      if (pos.iter->Right) {
        it.iter->Right = pos.iter->Right;
        pos.iter->Right->Parent = it.iter;
      }
    }
    if (pos.iter->Right == it.iter) {
      if (pos.iter->Left) {
        it.iter->Left = pos.iter->Left;
        pos.iter->Left->Parent = it.iter;
      }
    }
  } else {
    if (!it.iter->Left && !it.iter->Right) {
      if (it.iter->Parent->Left == it.iter) it.iter->Parent->Left = nullptr;
      if (it.iter->Parent->Right == it.iter) it.iter->Parent->Right = nullptr;
    } else {
      if (it.iter->Parent->Left == it.iter) {
        it.iter->Parent->Left = it.iter->Right;
      } else if (it.iter->Parent->Right == it.iter) {
        it.iter->Parent->Right = it.iter->Left;
      }
      if (it.iter->Right) {
        it.iter->Right->Parent = it.iter->Parent;
      } else {
        it.iter->Left->Parent = it.iter->Parent;
      }
    }
    if (pos.iter->Right) pos.iter->Right->Parent = it.iter;
    if (pos.iter->Left) pos.iter->Left->Parent = it.iter;
    it.iter->Left = pos.iter->Left;
    it.iter->Right = pos.iter->Right;
    it.iter->Parent = pos.iter->Parent;
  }
  if (pos.iter != root) {
    if (pos.iter->Parent->Left == pos.iter) pos.iter->Parent->Left = it.iter;
    if (pos.iter->Parent->Right == pos.iter) pos.iter->Parent->Right = it.iter;
  }
}

template <class Key>
void s21::set<Key>::suc_insert(s21::set<Key>::iterator &iter,
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
  ++size_;
}

// template <class Key>
// std::pair<s21::Iterator<Key>, bool> s21::set<Key>::key_check(const Key &key)
// {
//   iterator iter = begin();
//   bool coincidence = true;
//   while (coincidence && iter != end()) {
//     if (iter.iter->Key.first == key) {
//       coincidence = false;
//     } else {
//       ++iter;
//     }
//   }

//   return std::pair(iter, coincidence);
// }

template <class Key>
s21::Iterator<Key> s21::set<Key>::find(const Key &key) {
  iterator pos = begin();
  while (pos.iter->K != key && pos != end()) {
    ++pos;
  }
  return pos;
}

template <class Key>
void s21::set<Key>::SetSize(size_t val) {
  size_ = val;
}

template <class Key>
size_t s21::set<Key>::GetSize() {
  return size_;
}

template <class Key>
void s21::set<Key>::SetRoot(s21::Node<Key> *val) {
  root = val;
}

template <class Key>
s21::Node<Key> *s21::set<Key>::GetRoot() {
  return root;
}

template <class Key>
const s21::Node<Key> *s21::set<Key>::GetConstRoot() const {
  return root;
}

template <class Key>
template <class... Args>
std::vector<std::pair<s21::Iterator<Key>, bool>> s21::set<Key>::insert_many(
    Args &&...args) {
  std::vector<std::pair<s21::set<Key>::iterator, bool>> res;
  (res.push_back(insert(args)), ...);
  return res;
}