#ifndef CUDA_ADD_FOLD_H
#define CUDA_ADD_FOLD_H

#include "Array.hpp"


void add_on_gpu(std::size_t n, const float *src, float *dst);

template <typename T, std::size_t N>
void add_fold(const Array<T, N> &src, Array<T, N> &dst) {
  add_on_gpu(N, src.data(), dst.data());
}

#endif //CUDA_ADD_FOLD_H
