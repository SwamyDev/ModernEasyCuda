#include "AddFold.hpp"

__global__ void add(std::size_t  n, const float *x, float *y) {
  std::size_t  index = blockIdx.x * blockDim.x + threadIdx.x;
  std::size_t  stride = blockDim.x * gridDim.x;
  for (auto i = index; i < n; i += stride) y[i] = x[i] + y[i];
}

void add_on_gpu(std::size_t n, const float *src, float *dst) {
  std::size_t blockSize = 256;
  std::size_t numBlocks = (n + blockSize - 1)/blockSize;
  add<<<numBlocks, blockSize>>> (n, src, dst);

  cudaDeviceSynchronize();
}