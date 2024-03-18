#ifndef CONTAINERS_VECTOR_H_
#define CONTAINERS_VECTOR_H_

#include <initializer_list>
#include <iostream>
#include <iterator>
namespace containers {
template <typename T>
class vector {
 public:
  using size_type = std::size_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  vector() noexcept;
  explicit vector(size_t n);
  vector(std::initializer_list<T> const& items);
  vector(const vector<T>& v);
  vector(vector&& v) noexcept;
  ~vector();
  vector<T>& operator=(const vector<T>& v);
  vector<T>& operator=(vector<T>&& v) noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  size_type capacity() const noexcept;
  reference operator[](size_t i) const noexcept;

  reference at(size_type i) const;
  bool empty() const noexcept;
  void clear() noexcept;
  void push_back(const_reference value);
  void pop_back() noexcept;
  void reserve(size_type size);
  void shrink_to_fit();
  void swap(vector& other);
  const_reference front() const noexcept;
  const_reference back() const noexcept;
  T* data() const noexcept;
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  class VectorConstIterator {
   public:
    VectorConstIterator() noexcept : pos_(nullptr){};
    VectorConstIterator(value_type* it) noexcept : pos_(it) {}

    bool operator==(const VectorConstIterator& i) const noexcept {
      return pos_ == i.pos_;
    }

    bool operator!=(const VectorConstIterator& i) const noexcept {
      return pos_ != i.pos_;
    }

    VectorConstIterator operator++(int) noexcept {
      VectorConstIterator tmp = *this;
      pos_++;
      return tmp;
    }

    VectorConstIterator operator++() noexcept {
      ++pos_;
      return *this;
    }

    VectorConstIterator operator--(int) noexcept {
      auto tmp = *this;
      pos_--;
      return tmp;
    }

    VectorConstIterator operator--() noexcept {
      --pos_;
      return *this;
    }

    VectorConstIterator operator+(const size_type& index) const noexcept {
      auto tmp = *this;
      tmp.pos_ = pos_ + index;
      return tmp;
    }

    VectorConstIterator operator-(const size_type& index) const noexcept {
      auto tmp = *this;
      tmp.pos_ = pos_ - index;
      return tmp;
    }

    const_reference operator*() const noexcept { return *pos_; }

    value_type* pos_;
  };

  class VectorIterator : public VectorConstIterator {
   public:
    VectorIterator() noexcept : VectorConstIterator() { this->pos_ = nullptr; }
    VectorIterator(value_type* it) noexcept : VectorConstIterator(it) {
      this->pos_ = it;
    }

    VectorIterator operator++(int) noexcept {
      auto tmp = *this;
      this->pos_++;
      return tmp;
    }

    VectorIterator operator++() noexcept {
      ++this->pos_;
      return *this;
    }

    VectorIterator operator--(int) noexcept {
      auto tmp = *this;
      this->pos_--;
      return tmp;
    }

    VectorIterator operator--() noexcept {
      --this->pos_;
      return *this;
    }

    VectorIterator operator+(const size_type& index) const noexcept {
      auto tmp = *this;
      tmp.pos_ = this->pos_ + index;
      return tmp;
    }

    VectorIterator operator-(const size_type& index) const noexcept {
      auto tmp = *this;
      tmp.pos_ = this->pos_ - index;
      return tmp;
    }

    reference operator*() const noexcept { return *this->pos_; }
  };

  value_type* array_;
  size_type capacity_;
  size_type size_;

 public:
  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;

  iterator begin() const noexcept;
  iterator end() const noexcept;
  iterator insert(const_iterator pos, const_reference& value);
  void erase(iterator pos) noexcept;
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
};

template <typename T>
vector<T>::vector() noexcept : array_(nullptr), capacity_(0), size_(0) {}

template <typename T>
vector<T>::vector(size_t n) : capacity_(n), size_(n) {
  if (n < 1) {
    array_ = nullptr;
    std::bad_alloc();
  } else {
    array_ = new value_type[capacity_];
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<T> const& items)
    : capacity_(items.size()), size_(items.size()) {
  array_ = new value_type[capacity_]{0};
  for (size_t i = 0; i < size_; ++i) {
    array_[i] = *(items.begin() + i);
  }
}

template <typename T>
vector<T>::vector(const vector<T>& v) : capacity_(v.capacity_), size_(v.size_) {
  if (v.array_ == nullptr) {
    array_ = nullptr;
  } else {
    array_ = new value_type[capacity_]{0};
    for (size_type i = 0; i < size_; ++i) {
      array_[i] = v.array_[i];
    }
  }
}

template <typename T>
vector<T>::vector(vector<T>&& v) noexcept
    : array_(v.array_), capacity_(v.capacity_), size_(v.size_) {
  v.array_ = nullptr;
  v.capacity_ = 0;
  v.size_ = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] array_;
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& v) noexcept {
  if (this != &v) {
    delete[] array_;
    array_ = v.array_;
    capacity_ = v.capacity_;
    size_ = v.size_;
    v.array_ = nullptr;
    v.capacity_ = 0;
    v.size_ = 0;
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_t i) const noexcept {
  return array_[i];
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (capacity_ == size_) {
    if (capacity_ == 0) {
      ++capacity_;
    } else {
      capacity_ *= 2;
    }
    vector<T> tmp(capacity_);
    for (size_type i = 0; i < size_; ++i) {
      tmp.array_[i] = array_[i];
    }
    std::swap(array_, tmp.array_);
  }
  array_[size_] = value;
  ++size_;
}

template <typename T>
void vector<T>::pop_back() noexcept {
  if (size_ > 0) {
    --size_;
    array_[size_] = 0;
  }
}

template <typename T>
bool vector<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
void vector<T>::clear() noexcept {
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() const noexcept {
  VectorIterator tmp(array_);
  return tmp;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() const noexcept {
  VectorIterator tmp(array_ + size_);
  return tmp;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos,
                                               const_reference& value) {
  vector<T> tmp;
  vector<T>::iterator res;
  if (size_ != capacity_ && pos == this->end()) {
    array_[size_] = value;
    ++size_;
    return this->end() - 1;
  }
  if (size_ != capacity_) {
    tmp.reserve(size_ + 1);
  } else {
    capacity_ *= 2;
    tmp.reserve(capacity_);
  }
  for (auto i = this->begin(), j = tmp.begin(); i != this->end(); ++i) {
    if (i == pos) {
      *j = value;
      pos = j;
      res = vector<T>::iterator(j);
      ++j;
    }
    *j = *i;
    ++j;
  }
  std::swap(array_, tmp.array_);
  ++size_;
  return res;
}

template <typename T>
void vector<T>::erase(iterator pos) noexcept {
  if (pos != this->end() - 1) {
    for (auto i = pos; i != this->end() - 1; ++i) {
      *i = *(i + 1);
    }
  }
  --size_;
}

template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& v) {
  capacity_ = v.capacity_;
  size_ = v.size_;
  vector tmp(capacity_);
  for (size_type i = 0; i < size_; ++i) {
    tmp.array_[i] = v.array_[i];
  }
  std::swap(array_, tmp.array_);
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type i) const {
  if (capacity_ < i) {
    throw std::out_of_range("Incorrect index");
  }
  return array_[i];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const noexcept {
  return *array_;
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const noexcept {
  return array_[size_ - 1];
}

template <typename T>
T* vector<T>::data() const noexcept {
  return array_;
}
template <typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return size_type(-1) / sizeof(T) / 2;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > this->max_size())
    throw std::length_error("size cannot be larger than maximum size");
  if (size >= capacity_) {
    if (capacity_ < size) {
      capacity_ = size;
      vector<T> tmp(size);
      for (size_type i = 0; i < size_; ++i) {
        tmp.array_[i] = array_[i];
      }
      std::swap(array_, tmp.array_);
    }
  }
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (capacity_ == size_) return;
  vector<T> tmp(size_);
  for (size_type i = 0; i < size_; ++i) {
    tmp.array_[i] = array_[i];
  }
  std::swap(array_, tmp.array_);
  capacity_ = size_;
}

template <typename T>
void vector<T>::swap(vector& other) {
  if (this->begin() == other.begin()) return;
  std::swap(array_, other.array_);
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  for (auto& arg : {args...}) {
    push_back(arg);
  }
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  vector<T>::iterator res(pos.pos_);
  int cnt = 0;
  for (auto& arg : {args...}) {
    if (cnt == 0)
      res = insert(res, arg);
    else
      res = insert(res + 1, arg);
    cnt++;
  }
  return res - cnt;
}

}  // namespace containers

#endif  // CONTAINERS_VECTOR_H_