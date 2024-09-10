namespace s21 {

template <class T>
vector<T>::vector() {
  container_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <class T>
vector<T>::vector(size_t n) {
  capacity_ = n;
  size_ = n;
  container_ = new T[n];
}

template <class T>
vector<T>::vector(std::initializer_list<T> const &items) {
  this->capacity_ = this->size_ = items.size();
  if (this->size_) {
    this->container_ = new T[this->size_];
    std::copy(items.begin(), items.end(), this->container_);
  } else {
    this->conversion_to_zero();
  }
}

template <class T>
vector<T>::vector(const vector &v)
    : size_(v.size_), capacity_(v.capacity_), container_(new T[v.capacity_]) {
  std::copy(v.container_, v.container_ + v.size_, container_);
}

template <class T>
vector<T>::vector(vector &&other) noexcept
    : size_(other.size_),
      capacity_(other.capacity_),
      container_(other.container_) {
  other.size_ = 0;
  other.capacity_ = 0;
  other.container_ = nullptr;
}

template <class T>
vector<T>::~vector() {
  this->conversion_to_zero();
}

template <class T>
vector<T> &vector<T>::operator=(const vector &other) {
  if (this != &other) {
    delete[] container_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    container_ = new T[capacity_];
    std::copy(other.container_, other.container_ + size_, container_);
  }
  return *this;
}

template <class T>
vector<T> &vector<T>::operator=(vector &&other) noexcept {
  if (this != &other) {
    delete[] container_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    container_ = other.container_;
    other.size_ = 0;
    other.capacity_ = 0;
    other.container_ = nullptr;
  }
  return *this;
}

template <class T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("out of range (in function vector::at)");
  }
  return container_[pos];
}

template <class T>
typename vector<T>::reference vector<T>::operator[](size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("out of range (in function vector::operator[])");
  }
  return container_[pos];
}

template <class T>
typename vector<T>::const_reference vector<T>::front() const {
  if (size_ <= 0) {
    throw std::out_of_range("empty container (in function vector::front)");
  }
  return container_[0];
}

template <class T>
typename vector<T>::const_reference vector<T>::back() const {
  if (!size_) {
    throw std::out_of_range("empty container (in function vector::back)");
  }
  return container_[size_ - 1];
}

template <class T>
typename vector<T>::const_iterator vector<T>::data() const {
  return container_;
}

template <class T>
typename vector<T>::iterator vector<T>::data() {
  return container_;
}

template <class T>
T *vector<T>::begin() {
  return &container_[0];
}

template <class T>
const T *vector<T>::cbegin() const {
  return &container_[0];
}

template <class T>
T *vector<T>::end() {
  return &container_[size_];
}

template <class T>
const T *vector<T>::cend() const {
  return &container_[size_];
}

template <class T>
void vector<T>::reserve(size_type size) {
  if (size > capacity_) {
    T *tmp = new T[size];
    std::copy(this->begin(), this->end(), tmp);
    delete[] this->container_;
    this->capacity_ = size;
    this->container_ = tmp;
  }
}

template <class T>
size_t vector<T>::capacity() const {
  return capacity_;
}

template <class T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <class T>
typename vector<T>::size_type vector<T>::max_size() const {
  return capacity_;
}

template <class T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <class T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    T *newContainer = new T[size_];
    for (size_t i = 0; i < size_; ++i) {
      newContainer[i] = std::move(container_[i]);
    }
    delete[] container_;
    container_ = newContainer;
    capacity_ = size_;
  }
}

template <class T>
void vector<T>::push_back(const T &value) {
  if (capacity_ == size_) {
    reserve(2 * capacity_ + 1);
  }
  container_[size_] = value;
  ++size_;
}

template <class T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
  }
}

template <class T>
void vector<T>::clear() noexcept {
  size_ = 0;
}

template <class T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();
  if (size_ == capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }

  iterator new_pos = begin() + index;
  for (iterator it = end(); it > new_pos; --it) {
    *it = *(it - 1);
  }

  *new_pos = value;
  ++size_;
  return new_pos;
}

template <class T>
void vector<T>::erase(vector<T>::iterator pos) {
  std::move(pos + 1, end(), pos);
  pop_back();
}

template <class T>
void vector<T>::swap(vector<T> &other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(container_, other.container_);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  if (pos < this->begin() || pos > this->end()) {
    throw std::out_of_range("Iterator out of range");
  }
  size_type index = pos - this->begin();
  vector<T> temp({args...});
  size_type temp_size = temp.size();
  if (this->size() + temp_size > this->capacity()) {
    this->reserve(this->size() + temp_size);
  }
  iterator new_pos = this->begin() + index;
  std::move_backward(new_pos, this->end(), this->end() + temp_size);
  for (size_type i = 0; i < temp_size; ++i) {
    *(new_pos + i) = std::move(temp[i]);
  }
  this->size_ += temp_size;
  return new_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  (push_back(args), ...);
}

template <class T>
void vector<T>::conversion_to_zero() {
  delete[] container_;
  size_ = 0;
  capacity_ = 0;
  container_ = nullptr;
}

// template <class T>
// void vector<T>::print() {
//   for (size_t i = 0; i < this->size_; i++) {
//     std::cout << this->container_[i] << " ";
//   }
//   std::cout << std::endl;
// }

}  // namespace s21