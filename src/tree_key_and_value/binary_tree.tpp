namespace s21 {
template <typename K, typename V>
Iterator_<K, V>::Iterator_()
    : iter(nullptr), min_node(nullptr), max_node(nullptr){};

template <typename K, typename V>
Iterator_<K, V>::Iterator_(Node_<K, V> *it) {
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

template <typename K, typename V>
std::pair<K, V> &Iterator_<K, V>::operator*() {
  return this->iter->Key;
}

template <typename K, typename V>
Iterator_<K, V> Iterator_<K, V>::operator++() {
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

template <typename K, typename V>
Iterator_<K, V> Iterator_<K, V>::operator++(int) {
  Iterator_ prev_pos = iter;
  ++(*this);
  return prev_pos;
}

template <typename K, typename V>
Iterator_<K, V> Iterator_<K, V>::operator--() {
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

template <typename K, typename V>
Iterator_<K, V> Iterator_<K, V>::operator--(int) {
  Iterator_ prev_pos = iter;
  --(*this);
  return prev_pos;
}

template <typename K, typename V>
bool Iterator_<K, V>::operator==(const Iterator_ &other) {
  return iter == other.iter;
}

template <typename K, typename V>
bool Iterator_<K, V>::operator!=(const Iterator_ &other) {
  return iter != other.iter;
}

template <typename K, typename V>
Tree<K, V>::Tree() : root(nullptr), size_(){};

template <class K, class V>
Tree<K, V>::Tree(Tree<K, V> &&m) : Tree() {
  *this = std::move(m);
}

template <class K, class V>
Tree<K, V>::Tree(const std::initializer_list<std::pair<K, V>> &items) {
  for (const auto &el : items) {
    insert(el);
  }
}

template <class K, class V>
Tree<K, V>::Tree(const Tree<K, V> &m) : Tree() {
  Iterator_<K, V> pos = m.root;
  while (pos.iter) {
    insert(pos.iter->Key);
    ++pos;
  }
  pos = m.root;
  while (pos.iter) {
    insert(pos.iter->Key);
    --pos;
  }
}

template <class K, class V>
Tree<K, V>::~Tree() {
  clear();
}

template <class K, class V>
Tree<K, V> &Tree<K, V>::operator=(Tree<K, V> &&m) {
  if (this != &m) {
    clear();
    this->root = m.root;
    this->size_ = m.size_;
    m.root = nullptr;
    m.size_ = 0;
  }
  return *this;
}

template <class K, class V>
void Tree<K, V>::clear() {
  Iterator_<K, V> pos = begin();
  while (!empty()) {
    erase(pos);
    ++pos;
  }
}

template <class K, class V>
bool Tree<K, V>::empty() {
  return !size_;
}

template <class K, class V>
size_t Tree<K, V>::size() {
  return size_;
}

template <typename K, typename V>
Iterator_<K, V> Tree<K, V>::begin() {
  Iterator_<K, V> pos = root;
  if (!empty()) {
    while (pos.iter->Left) {
      pos.iter = pos.iter->Left;
    }
  }
  return pos;
}

template <typename K, typename V>
Iterator_<K, V> Tree<K, V>::end() {
  Iterator_<K, V> pos = nullptr;
  return pos;
}

template <typename K, typename V>
V &Tree<K, V>::operator[](const K &key) {
  Iterator_<K, V> pos;
  std::pair<Iterator_<K, V>, bool> coincidence = key_check(key);
  if (coincidence.second) {
    coincidence.first = insert(std::pair(key, V())).first;
  }
  pos = coincidence.first;
  return pos.iter->Key.second;
}

template <class K, class V>
V &Tree<K, V>::at(const K &key) {
  Iterator_<K, V> pos;
  std::pair<Iterator_<K, V>, bool> coincidence = key_check(key);
  if (coincidence.second) {
    throw std::out_of_range("no key in this map");
  }
  pos = coincidence.first;
  return pos.iter->Key.second;
}

template <class K, class V>
std::pair<Iterator_<K, V>, bool> Tree<K, V>::key_check(const K &key) {
  Iterator_<K, V> iter = begin();
  bool coincidence = true;
  while (coincidence && iter != end()) {
    if (iter.iter->Key.first == key) {
      coincidence = false;
    } else {
      ++iter;
    }
  }
  return std::pair(iter, coincidence);
}

template <typename K, typename V>
void Tree<K, V>::erase(Iterator_<K, V> pos) {
  Iterator_<K, V> iter_pos = pos;
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

template <typename K, typename V>
void Tree<K, V>::pos_swap(Iterator_<K, V> &pos, Iterator_<K, V> &it) {
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

template <class K, class V>
std::pair<Iterator_<K, V>, bool> Tree<K, V>::insert(
    const std::pair<K, V> &value) {
  Iterator_<K, V> iter = this->root;
  bool succses = true;
  if (!size_) {
    Node_<K, V> *current = new Node_<K, V>(value);
    iter.iter = current;
    root = iter.iter;
    ++size_;
  } else {
    succses = contains(value.first);
    if (!succses) {
      suc_insert(iter, value);
    }
  }

  return std::pair(iter, !succses);
}

template <class K, class V>
bool Tree<K, V>::contains(const K &key) {
  bool res = false;
  Iterator_<K, V> pos = begin();
  while (pos.iter && !res) {
    if (pos.iter->Key.first == key) {
      res = true;
    }
    ++pos;
  }
  return res;
}

template <class K, class V>
void Tree<K, V>::suc_insert(Iterator_<K, V> &iter,
                            const std::pair<K, V> &value) {
  Iterator_<K, V> Parent;
  bool b = true;
  Node_<K, V> *current = new Node_<K, V>(value);
  while (b) {
    if (iter.iter->Key.first > value.first) {
      if (iter.iter->Left == nullptr) {
        iter.iter->Left = current;
        iter.iter->Left->Parent = iter.iter;
        b = false;
      } else {
        Parent = iter;
        iter = iter.iter->Left;
      }
    } else if (iter.iter->Key.first <= value.first) {
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

template <class K, class V>
std::pair<s21::Iterator_<K, V>, bool> s21::Tree<K, V>::insert_or_assign(
    const K &key, const V &obj) {
  bool check = contains(key);
  (*this)[key] = obj;
  std::pair<s21::Iterator_<K, V>, bool> res = (*this).key_check(key);
  if (!check) res.second = true;
  return res;
}

template <typename K, typename V>
size_t Tree<K, V>::max_size() {
  return (std::numeric_limits<size_t>::max() / sizeof(Tree<K, V>) / 5);
}

}  // namespace s21