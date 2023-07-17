#include "Vect.h"

template <typename T> Vect<T>::Vect(std::initializer_list<T> l) {
  size_ = l.size();
  capacity_ = size_ * 2;
  pointer = new T[size_];
  int i = 0;
  for (auto elem : l) {
    pointer[i] = elem;
    i++;
  }
}

template <typename T> inline Vect<T>::Vect() {
  pointer = new T[1];
  size_ = 1;
};

template <typename T> Vect<T>::Vect(Vect &&moved) {
  pointer = moved.pointer;
  size_ = moved.size_;
  capacity_ = moved.capacity_;
  moved.pointer = nullptr;
  moved.size_ = 0;
  moved.capacity_ = 0;
};

template <typename T> Vect<T>::Vect(const Vect &other) {
  pointer = new T[other.size_];
  size_ = other.size_;
  capacity_ = other.capacity_;
  for (int i = 0; i < other.size_; i++) {
    pointer[i] = other.pointer[i];
  }
}

template <typename T> inline Vect<T>::Vect(size_t size) {
  pointer = new T[size];
  size_ = size;
}

template <typename T> Vect<T>::Vect(int size, ...) {
  pointer = new T[size * 2];
  capacity_ = size * 2;
  va_start(ap, size);
  for (int i = 0; i < size; i++) {
    pointer[i] = va_arg(ap, T);
  }
  size_ = size;
}

template <typename T> void Vect<T>::reallocate() {
  if (size_ == 0) {
    size_ = 1;
    capacity_ = 2;
    pointer = new T[capacity_];
    return;
  }
  T *tmp = new T[size_ * 2];
  capacity_ = size_ * 2;
  for (int i = 0; i < size_; i++) {
    tmp[i] = pointer[i];
  }
  delete[] pointer;
  pointer = tmp;
}

template <typename T> inline void Vect<T>::push_back(T elem) {
  if (size_ == 0) {
    reallocate();
    pointer[0] = elem;
    return;
  }
  if (size_ + 1 >= capacity_)
    reallocate();
  pointer[size_++] = elem;
}

template <typename T> inline T Vect<T>::last() { return pointer[size_ - 1]; }

template <typename T> Vect<T>::~Vect() {
#ifdef MESSAGE
  std::cout << "destructor for " << pointer << " called\n";
#endif
  if (pointer != nullptr)
    delete[] pointer;
}

template <typename T> size_t Vect<T>::size() { return size_; }

template <typename T>
inline std::ostream &operator<<(std::ostream &os, Vect<T> &vec) {
  for (int i = 0; i < vec.size(); i++)
    os << vec[i] << " ";
  return os;
}

template <typename T> T &Vect<T>::operator[](int index) {
  try {
    if (index >= size_)
      throw(std::runtime_error("out of range"));
  } catch (std::runtime_error s) {
    s.what();
  }
  return pointer[index];
}

template <typename T> void Vect<T>::emplace_at(size_t index) {
  try {
    if (index >= size_)
      throw(std::runtime_error("out of range"));
    else {
      for (size_t i = index + 1; i < size_; ++i) {
        pointer[i - 1] = pointer[i];
      }
      --size_;
      capacity_ = size_ * 2;
    }
  } catch (std::runtime_error s) {
    std::cout << s.what() << std::endl;
  }
}

template <typename T> inline void Vect<T>::pop_back() {
  size_--;
  capacity_ = size_ * 2;
}

template <typename T> inline size_t Vect<T>::get_capacity() {
  return capacity_;
}

template <typename T> inline void Vect<T>::push_front(T elem) {
  size_++;
  if (size_ >= capacity_)
    reallocate();
  pointer[size_] = elem;
}

template <typename T> inline void Vect<T>::pop_front() {
  T *tmp = pointer;
  pointer = new T[size_ - 1];
  for (int i = 1; i < size_; i++) {
    pointer[i - 1] = tmp[i];
  }
  size_--;
  capacity_ = size_ * 2;
  delete[] tmp;
}

template <typename T> T *Vect<T>::find(T *begin, T *end, T value) {
  while (begin != end) {
    if (*begin == value)
      return begin;
    begin++;
  }
  return end;
}

template <typename T>
T *Vect<T>::find_if(T *begin, T *end, bool (*condition)(T)) {
  while (begin != end) {
    if (condition(*begin))
      return begin;
    begin++;
  }
  return end;
}

template <typename T>
T *Vect<T>::find_if_not(T *begin, T *end, bool (*condition)(T)) {
  while (begin != end) {
    if (!condition(*begin))
      return begin;
    begin++;
  }
  return end;
}

template <typename T>
void Vect<T>::insert(T *iter, std::initializer_list<T> l) {
  int tmp = size_;
  size_ += l.size();
  if (size_ >= capacity_)
    reallocate();
  for (int i = size_; &pointer[i] != iter; i--) {
    pointer[i] = pointer[tmp--];
  }
  for (auto elem : l) {
    *iter++ = elem;
  }
}

template <typename T> inline T Vect<T>::first() { return pointer[0]; }

template <typename T>
void Vect<T>::sort(T *begin, T *end, bool (*compare)(T, T)) {
  if (begin < end) {
    T pivot = *begin;
    T *left = begin + 1;
    T *right = end;

    while (left <= right) {
      while (left <= end && compare(*left, pivot))
        left++;

      while (right > begin && !compare(*right, pivot))
        right--;

      if (left < right)
        std::swap(*left, *right);
    }

    std::swap(*begin, *right);

    sort(begin, right - 1, compare);
    sort(right + 1, end, compare);
  }
}

int main() {
  Vect<int> v = {142, 142, 5124, 5, 3, 212, 45, 121, 4};
  v.sort(v.begin(), v.end());
  std::cout << v << std::endl;
}