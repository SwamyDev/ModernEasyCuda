#ifndef CUDA_ARRAYITERATOR_H
#define CUDA_ARRAYITERATOR_H

#include <iterator>

template <typename ArrayT, typename ElemT>
class ArrayIterator {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = ElemT;
  using pointer = value_type*;
  using reference = value_type&;
  using difference_type = std::size_t;

  ArrayIterator() = default;
  ArrayIterator(ArrayT &a, std::size_t idx) : maybeArray(&a), itsIndex(idx) {}

  reference operator*() {
    return (*maybeArray)[itsIndex];
  }

  pointer operator->() {
    return &(*maybeArray)[itsIndex];
  }

  ArrayIterator<ArrayT, ElemT> &operator++() {
    ++itsIndex;
    return *this;
  }

  const ArrayIterator<ArrayT, ElemT> operator++(int) {
    auto i = itsIndex++;
    return {*maybeArray, i};
  }

  ArrayIterator<ArrayT, ElemT> &operator--() {
    --itsIndex;
    return *this;
  }

  const ArrayIterator<ArrayT, ElemT> operator--(int) {
    auto i = itsIndex--;
    return {*maybeArray, i};
  }

  ArrayIterator<ArrayT, ElemT> &operator+=(difference_type n) {
    itsIndex+=n;
    return *this;
  }

  ArrayIterator<ArrayT, ElemT> &operator-=(difference_type n) {
    itsIndex-=n;
    return *this;
  }

  bool operator==(const ArrayIterator<ArrayT, ElemT> &other) {
    return maybeArray == other.maybeArray && itsIndex == other.itsIndex;
  }

  bool operator!=(const ArrayIterator<ArrayT, ElemT> &other) {
    return !(*this==other);
  }

private:
  ArrayT* maybeArray;
  std::size_t itsIndex = 0;
};




#endif //CUDA_ARRAYITERATOR_H
