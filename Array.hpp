#ifndef CUDA_ARRAY_H
#define CUDA_ARRAY_H

#include <cstring>
#include <memory>
#include <utility>
#include "ArrayIterator.hpp"
#include "cuda_runtime_api.h"

template<typename T, std::size_t N>
T *AllocCudaArray() {
  T *raw;
  cudaMallocManaged(reinterpret_cast<void **>(&raw), N*sizeof(T));
  return raw;
}

template<typename T, std::size_t N>
class Array {
public:
  using iterator = ArrayIterator<Array<T, N>, T>;
  Array() : blob(AllocCudaArray<T, N>(), cudaFree) {}

  explicit Array(const T &value) : Array() {
    for (auto i = 0; i < N; ++i)
      (*this)[i] = value;
  }

  Array(const Array<T, N> &other) : Array() { CopyFrom(other); }

  Array<T, N> &operator=(const Array<T, N> &other) {
    if (&other==this)  // very important! otherwise behaviour is undefined
      return *this;

    CopyFrom(other);
    return *this;
  }

  Array(Array<T, N> &&other) noexcept = default;
  Array<T, N> &operator=(Array<T, N> &&other) noexcept = default;

  iterator begin() { return iterator(*this, 0); }
  iterator end() { return iterator(*this, N); }

  T &operator[](std::size_t idx) { return blob[idx]; }
  const T &operator[](std::size_t idx) const { return blob[idx]; }

  T *data() { return blob.get(); }
  const T *data() const { return blob.get(); }

private:
  void CopyFrom(const Array<T, N> &other) {
    std::memcpy(data(), other.data(), N*sizeof(T));
  }
  std::unique_ptr<T[], decltype(&cudaFree)> blob;
};

template<typename T, std::size_t N>
bool operator==(const Array<T, N> &lhs, const Array<T, N> &rhs) {
  for (auto i = 0; i < N; ++i) {
    if (lhs[i]!=rhs[i])
      return false;
  }

  return true;
}

template<typename T, std::size_t N>
bool operator!=(const Array<T, N> &lhs, const Array<T, N> &rhs) {
  return !(lhs==rhs);
}

#endif //CUDA_ARRAY_H
