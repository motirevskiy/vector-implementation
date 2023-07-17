#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <exception>
#include <initializer_list>
#include <iostream>

template <typename T> class Vect {

public:
  Vect();
  Vect(size_t size);
  Vect(int size, ...);
  Vect(std::initializer_list<T> l);
  Vect(const Vect &other);
  Vect(Vect &&moved);
  ~Vect();

  void push_back(T elem);
  void emplace_at(size_t index);
  void pop_back();
  void push_front(T elem);
  void pop_front();
  void insert(T *iter, std::initializer_list<T> l);
  void sort(T *begin, T *end, bool (*compare)(T, T));
  void sort(T *begin, T *end) {
    sort(begin, end, [](T a, T b) { return a < b; });
  }

  T &operator[](int index);

  T &at(int index) { return pointer[index]; }
  T *begin() { return &pointer[0]; }
  const T *begin() const { return &pointer[0]; }
  const T *end() const { return &pointer[size_ - 1]; }
  T *end() { return &pointer[size_ - 1]; }

  T first();
  T last();

  T *find(T *begin, T *end, T value);
  T *find_if(T *begin, T *end, bool (*condition)(T));
  T *find_if_not(T *begin, T *end, bool (*condition)(T));

  size_t get_capacity();
  size_t size();

private:
  T *pointer = nullptr;
  va_list ap;
  size_t size_;
  size_t capacity_;
  void reallocate();
};

#endif