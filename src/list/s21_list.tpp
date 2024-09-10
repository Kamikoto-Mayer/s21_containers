template <class T>
s21::list<T>::ListIterator::ListIterator() : ptr_(nullptr), eage(nullptr){};

template <class T>
s21::list<T>::ListIterator::ListIterator(s21::list<T> &ptr) : ListIterator() {
  ptr_ = ptr.head_;
  eage = &ptr;
}

template <class T>
T &s21::list<T>::ListIterator::operator*() {
  static T default_value;
  if (ptr_ == nullptr) return default_value;
  return ptr_->value_;
}

template <class T>
typename s21::list<T>::ListIterator &s21::list<T>::ListIterator::operator++() {
  if (ptr_ == nullptr) {
    ptr_ = eage->head_;
  } else {
    ptr_ = ptr_->next_;
  }
  return *this;
}

template <class T>
typename s21::list<T>::ListIterator s21::list<T>::ListIterator::operator++(
    int) {
  ListIterator *tmp;
  tmp = this;
  if (ptr_ == nullptr) {
    ptr_ = eage->head_;
  } else {
    ptr_ = ptr_->next_;
  }
  return *tmp;
}

template <class T>
typename s21::list<T>::ListIterator &s21::list<T>::ListIterator::operator--() {
  if (ptr_ == nullptr) {
    ptr_ = eage->tail_;
  } else {
    ptr_ = ptr_->prev_;
  }
  return *this;
}

template <class T>
typename s21::list<T>::ListIterator s21::list<T>::ListIterator::operator--(
    int) {
  ListIterator *tmp;
  tmp = this;
  if (ptr_ == nullptr) {
    ptr_ = eage->tail_;
  } else {
    ptr_ = ptr_->prev_;
  }
  return *tmp;
}

template <class T>
bool s21::list<T>::ListIterator::operator==(
    const s21::list<T>::ListIterator &other) {
  return ptr_ == other.ptr_;
}

template <class T>
bool s21::list<T>::ListIterator::operator!=(
    const s21::list<T>::ListIterator &other) {
  return ptr_ != other.ptr_;
}

template <class T>
s21::list<T>::list() : head_(nullptr), tail_(nullptr), size_(){};

template <class T>
s21::list<T>::list(size_t n) : list() {
  while (n) {
    push_back(value_type());
    --n;
  }
}

template <class T>
s21::list<T>::list(const std::initializer_list<T> &items) : list() {
  for (auto Element : items) {
    push_back(Element);
  }
}

template <class T>
s21::list<T>::list(const s21::list<T> &l) : list() {
  Node *tmp = l.head_;
  while (tmp) {
    push_back(tmp->value_);
    tmp = tmp->next_;
  }
}

template <class T>
s21::list<T>::list(s21::list<T> &&l) : list() {
  swap(l);
}

template <class T>
s21::list<T>::~list() {
  (*this).clear();
}

template <class T>
s21::list<T> &s21::list<T>::operator=(s21::list<T> &&l) {
  if (this != &l) {
    clear();
    swap(l);
  }
  return *this;
}

template <typename T>
s21::list<T> &s21::list<T>::operator=(const list<T> &other) {
  if (this != &other) {
    clear();
    list<T> temp(other);
    swap(temp);
  }
  return *this;
}

template <class T>
bool s21::list<T>::empty() {
  return !size_;
}

template <class T>
size_t s21::list<T>::size() {
  return size_;
}

template <class T>
size_t s21::list<T>::max_size() {
  return (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
}

template <typename value_type>
void s21::list<value_type>::push_back(const_reference value) {
  Node *current = new Node(value);
  if (head_ == nullptr) {
    head_ = current;
    tail_ = current;
  } else {
    current->prev_ = tail_;
    tail_->next_ = current;
    tail_ = current;
  }
  size_++;
}

template <class T>
void s21::list<T>::pop_back() {
  Node *tmp = tail_;
  if (size_ == 1) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    tail_ = tail_->prev_;
    tail_->next_ = nullptr;
  }
  delete tmp;
  size_--;
}

template <class T>
void s21::list<T>::push_front(const T &value) {
  Node *current = new Node(value);
  if (head_ == nullptr) {
    head_ = current;
    tail_ = current;
  } else {
    current->next_ = head_;
    head_->prev_ = current;
    head_ = current;
  }
  size_++;
}

template <class T>
void s21::list<T>::pop_front() {
  Node *tmp = head_;
  if (size_ == 1) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    head_ = head_->next_;
    head_->prev_ = nullptr;
  }
  delete tmp;
  size_--;
}

template <class T>
void s21::list<T>::swap(s21::list<T> &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <class T>
void s21::list<T>::merge(s21::list<T> &other) {
  iterator it_a = *this;
  iterator it_b = other;
  list<value_type> tmp;
  bool stop_a = 1;
  bool stop_b = 1;
  for (size_t i = 0; i < size_ + other.size_; i++)
    if ((*it_a > *it_b && stop_b) || !stop_a) {
      tmp.push_back(it_b.ptr_->value_);
      if (it_b.ptr_->next_ == nullptr) {
        stop_b = 0;
      }
      it_b++;
    } else {
      tmp.push_back(it_a.ptr_->value_);
      if (it_a.ptr_->next_ == nullptr) stop_a = 0;
      it_a++;
    }
  other.clear();
  *this = std::move(tmp);
}

template <class T>
void s21::list<T>::reverse() {
  list<value_type> tmp;
  iterator pos = *this;
  --pos;
  --pos;
  for (size_t i = 0; i < size_; i++) {
    tmp.push_back(pos.ptr_->value_);
    --pos;
  }
  *this = std::move(tmp);
}

template <class T>
void s21::list<T>::unique() {
  iterator pos = *this;
  int size_list = size_;
  for (int i = 1; i < size_list; i++) {
    if (pos.ptr_->value_ == pos.ptr_->next_->value_) {
      erase(pos);
    }
    ++pos;
  }
}

template <class T>
void s21::list<T>::sort() {
  value_type tmp{};
  iterator pos = *this;
  int check = 1;
  for (size_t i = 0, node_size = size_; i < size_ - 1 && check; i++) {
    for (size_t j = 1; j < node_size - 1; j++) {
      check = 0;
      if (pos.ptr_->value_ > pos.ptr_->next_->value_) {
        tmp = pos.ptr_->value_;
        pos.ptr_->value_ = pos.ptr_->next_->value_;
        pos.ptr_->next_->value_ = tmp;
        check = 1;
      }
      pos++;
    }
    node_size--;
    pos.ptr_ = (*this).head_;
  }
}

template <class T>
typename s21::list<T>::iterator s21::list<T>::begin() {
  iterator iter_begin = *this;
  return iter_begin;
}

template <class T>
typename s21::list<T>::iterator s21::list<T>::end() {
  iterator iter_end = *this;
  --iter_end;
  return iter_end;
}

template <class T>
typename s21::list<T>::iterator s21::list<T>::insert(s21::list<T>::iterator pos,
                                                     const T &value) {
  if (pos.ptr_ == head_) {
    push_front(value);
  } else if (pos.ptr_ == nullptr) {
    push_back(value);
  } else {
    Node *new_node = new Node(value);
    Node *tmp = pos.ptr_;
    new_node->prev_ = tmp->prev_;
    new_node->next_ = tmp;
    tmp->prev_->next_ = new_node;
    tmp->prev_ = new_node;
    size_++;
  }
  return pos;
}

template <class T>
void s21::list<T>::erase(s21::list<T>::iterator pos) {
  if (!size_) {
    throw std::range_error("no element of list");
  }
  if (pos.ptr_ == head_) {
    head_ = pos.ptr_->next_;
    head_->prev_ = nullptr;
  } else if (pos.ptr_ == tail_) {
    tail_ = pos.ptr_->prev_;
    tail_->next_ = nullptr;
  } else {
    pos.ptr_->prev_->next_ = pos.ptr_->next_;
    pos.ptr_->next_->prev_ = pos.ptr_->prev_;
  }
  size_--;
  delete pos.ptr_;
}

template <class T>
void s21::list<T>::splice(s21::list<T>::const_iterator pos,
                          s21::list<T> &other) {
  Node *pos_this = pos.ptr_;
  if (pos_this == head_) {
    other.tail_->next_ = head_;
    head_->prev_ = other.tail_;
    head_ = other.head_;
  } else {
    pos_this->prev_->next_ = other.head_;
    other.head_->prev_ = pos_this->prev_;
    other.tail_->next_ = pos_this;
    pos_this->prev_ = other.tail_;
  }
  size_ += other.size_;
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <class T>
void s21::list<T>::clear() {
  while (!empty()) {
    pop_back();
  }
}

template <class T>
const T &s21::list<T>::front() {
  return head_->value_;
}

template <class T>
const T &s21::list<T>::back() {
  return tail_->value_;
}

template <class T>
template <class... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(
    s21::list<T>::const_iterator pos, Args &&...args) {
  (insert(pos, args), ...);
  return pos;
}

template <class T>
template <class... Args>
void s21::list<T>::insert_many_back(Args &&...args) {
  (push_back(args), ...);
}

template <class T>
template <class... Args>
void s21::list<T>::insert_many_front(Args &&...args) {
  (push_front(args), ...);
}