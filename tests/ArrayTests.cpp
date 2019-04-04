#include "catch.hpp"
#include <chrono>

#include "Array.hpp"
#include "AddFold.hpp"

using namespace std::chrono_literals;
using namespace std::chrono;

template<typename FuncT, typename... Args>
milliseconds TimeIt(FuncT &&f, Args &&... args) {
  auto start = system_clock::now();
  f(std::forward<Args>(args)...);
  return duration_cast<milliseconds>(system_clock::now() - start);
}

TEST_CASE("Arrays provide equality operators") {
  constexpr std::size_t size = 10;
  REQUIRE(Array<float, size>(1.0f)==Array<float, size>(1.0f));
  REQUIRE(Array<float, size>(1.0f)!=Array<float, size>(2.0f));
}

TEST_CASE("Add fold adds each element of the source array to the destination array") {
  constexpr std::size_t size = 10;
  Array<float, size> a(1.0f);
  Array<float, size> b(2.0f);

  add_fold(a, b);

  REQUIRE(b==Array<float, size>(3.0f));
}

TEST_CASE("Add fold one array into another with each containing 1 million elements takes not more than 2ms",
          "[performance]") {
  constexpr std::size_t size = 1 << 20; // ~ 1M
  constexpr std::size_t numSamples = 1000;
  Array<float, size> a(1.0f);
  Array<float, size> b(2.0f);

  auto total = 0ms;
  for (auto _ = 0; _ < numSamples; ++_) {
    total += TimeIt(add_fold<float, size>, a, b);
  }

  auto avgTime = (total / numSamples);
  REQUIRE(avgTime < 2ms);
}