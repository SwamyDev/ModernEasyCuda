cmake_minimum_required(VERSION 3.7)
project(cuda)
find_package(CUDA QUIET REQUIRED)

set(CMAKE_CXX_STANDARD 14)

include(CTest)

cuda_add_library(array Array.hpp AddFold.hpp AddFold.cu)
add_executable(array_tests tests/main.cpp tests/ArrayTests.cpp)
target_include_directories(array_tests PRIVATE .)
target_link_libraries(array_tests PRIVATE array)

add_test(all array_tests)
add_test(gpu_performance nvprof --log-file nvprof_test.log ./array_tests [performance])
