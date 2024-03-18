#ifndef CONTAINERS_ARRAY_H_
#define CONTAINERS_ARRAY_H_

#include <initializer_list>
#include <iostream>
#include <iterator>

namespace containers {
template <typename T, std::size_t N>
class array {
 public:
  using size_type = std::size_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  array() noexcept;
  array(std::initializer_list<value_type> const& items);
  array(const array<T, N>& a);
  array(array&& a) noexcept;
  ~array();
  array<T, N>& operator=(const array<T, N>& a);
  array<T, N>& operator=(array<T, N>&& a) noexcept;
  size_type max_size() const noexcept;
  reference operator[](size_t i) const noexcept;

  reference at(size_type i) const;
  size_type size() const noexcept;
  bool empty() const noexcept;
  void swap(array& other);
  const_reference front() const noexcept;
  const_reference back() const noexcept;
  void fill(const_reference value) noexcept;

 private:
  class ArrayConstIterator {
   public:
    ArrayConstIterator() noexcept : pos_(nullptr){};
    ArrayConstIterator(value_type* it) noexcept : pos_(it) {}

    bool operator==(const ArrayConstIterator& i) const noexcept {
      return pos_ == i.pos_;
    }

    bool operator!=(const ArrayConstIterator& i) const noexcept {
      return pos_ != i.pos_;
    }

    ArrayConstIterator operator++(int) noexcept {
      ArrayConstIterator tmp = *this;
      pos_++;
      return tmp;
    }

    ArrayConstIterator operator++() noexcept {
      ++pos_;
      return *this;
    }

    ArrayConstIterator operator--(int) noexcept {
      auto tmp = *this;
      pos_--;
      return tmp;
    }

    ArrayConstIterator operator--() noexcept {
      --pos_;
      return *this;
    }

    ArrayConstIterator operator+(const size_type& index) const noexcept {
      auto tmp = *this;
      tmp.pos_ = pos_ + index;
      return tmp;
    }

    ArrayConstIterator operator-(const size_type& index) const noexcept {
      auto tmp = *this;
      tmp.pos_ = pos_ - index;
      return tmp;
    }

    const_reference operator*() const noexcept { return *pos_; }

   protected:
    value_type* pos_;
  };

  class ArrayIterator : public ArrayConstIterator {
   public:
    ArrayIterator() noexcept : ArrayConstIterator() { this->pos_ = nullptr; }
    ArrayIterator(value_type* it) noexcept : ArrayConstIterator(it) {
      this->pos_ = it;
    }

    ArrayIterator operator++(int) noexcept {
      auto tmp = *this;
      this->pos_++;
      return tmp;
    }

    ArrayIterator operator++() noexcept {
      ++this->pos_;
      return *this;
    }

    ArrayIterator operator--(int) noexcept {
      auto tmp = *this;
      this->pos_--;
      return tmp;
    }

    ArrayIterator operator--() noexcept {
      --this->pos_;
      return *this;
    }

    ArrayIterator operator+(const size_type& index) const noexcept {
      auto tmp = *this;
      tmp.pos_ = this->pos_ + index;
      return tmp;
    }

    ArrayIterator operator-(const size_type& index) const noexcept {
      auto tmp = *this;
      tmp.pos_ = this->pos_ - index;
      return tmp;
    }

    reference operator*() const noexcept { return *this->pos_; }
  };

  value_type array_[N];
  size_type size_ = N;

 public:
  using iterator = ArrayIterator;
  using const_iterator = ArrayConstIterator;

  iterator data() const noexcept;
  iterator begin() const noexcept;
  iterator end() const noexcept;
};

template <typename T, std::size_t N>
array<T, N>::array() noexcept : size_(N) {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items) {
  for (size_t i = 0; i < size_; ++i) {
    array_[i] = *(items.begin() + i);
  }
}

template <typename T, std::size_t N>
array<T, N>::array(const array<T, N>& a) {
  for (size_type i = 0; i < size_; ++i) {
    array_[i] = a.array_[i];
  }
}

template <typename T, std::size_t N>
array<T, N>::array(array<T, N>&& a) noexcept {
  for (size_type i = 0; i < size_; ++i) {
    array_[i] = a.array_[i];
  }
}

template <typename T, std::size_t N>
array<T, N>::~array() {}

template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(array<T, N>&& a) noexcept {
  if (this != &a) {
    for (size_type i = 0; i < size_; ++i) {
      array_[i] = a.array_[i];
    }
  }
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](
    size_t i) const noexcept {
  return (reference)array_[i];
}

template <typename T, std::size_t N>
bool array<T, N>::empty() const noexcept {
  return size_ == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() const noexcept {
  ArrayIterator tmp((value_type*)array_);
  return tmp;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() const noexcept {
  ArrayIterator tmp((value_type*)array_);
  return tmp;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() const noexcept {
  ArrayIterator tmp((value_type*)array_ + size_);
  return tmp;
}

template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(const array<T, N>& a) {
  for (size_type i = 0; i < size_; ++i) {
    array_[i] = a.array_[i];
  }
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type i) const {
  if (size_ - 1 < i) {
    throw std::out_of_range("Incorrect index");
  }
  return (reference)array_[i];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const noexcept {
  return *array_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const noexcept {
  return array_[size_ - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return size_;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return size_;
}

template <typename T, std::size_t N>
void array<T, N>::swap(array& other) {
  if (this->begin() == other.begin()) return;
  std::swap(array_, other.array_);
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) noexcept {
  for (size_type i = 0; i < size_; ++i) {
    array_[i] = value;
  }
}

}  // namespace containers

#endif  // CONTAINERS_ARRAY_H_