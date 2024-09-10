#include "s21_queue.h"

namespace s21 {

// Queue Member functions
template <class T, class Container>
queue<T, Container>::queue() : container_(){};

template <class T, class Container>
queue<T, Container>::queue(std::initializer_list<T> const &items)
    : container_(items){};

template <class T, class Container>
queue<T, Container>::queue(const queue<T, Container> &q)
    : container_(q.container_){};

template <class T, class Container>
queue<T, Container>::queue(queue<T, Container> &&q)
    : container_(std::move(q.container_)){};

template <class T, class Container>
queue<T, Container>::~queue(){

};

template <typename T, typename Container>
queue<T, Container> &queue<T, Container>::operator=(
    const queue<T, Container> &other) {
  if (this != &other) {
    this->container_ = other.container_;
  }
  return *this;
}

template <typename T, typename Container>
queue<T, Container> &queue<T, Container>::operator=(queue<T, Container> &&q) {
  this->container_ = std::move(q.container_);
  return *this;
}

// Queue Element access
template <class T, class Container>
const T &s21::queue<T, Container>::front() {
  return container_.front();
}

template <class T, class Container>
const T &s21::queue<T, Container>::back() {
  return container_.back();
}

// Queue Capacity
template <class T, class Container>
bool queue<T, Container>::empty() {
  return this->container_.empty();
}

// Queue Modifiers
template <class T, class Container>
typename queue<T, Container>::size_type queue<T, Container>::size() {
  return this->container_.size();
}

template <class T, class Container>
void queue<T, Container>::push(const_reference value) {
  this->container_.push_back(value);
}

template <class T, class Container>
void queue<T, Container>::pop() {
  this->container_.pop_front();
}

template <class T, class Container>
void queue<T, Container>::swap(queue &other) {
  std::swap(this->container_, other.container_);
}

// insert many
template <class T, class Container>
template <typename... Args>
void queue<T, Container>::insert_many_back(Args &&...args) {
  (this->container_.push_back(args), ...);
}

}  // namespace s21