#define CATCH_CONFIG_MAIN
#include <iostream>

#include "catch.hpp"
#include "src/io_util.h"
#include "src/thread_pool.h"

template <typename T>
static T add(T x, T y) {
  return x + y;
}
template <typename T>
static T sub(T x, T y) {
  return x - y;
}
template <typename T>
static T mul(T x, T y) {
  return x * y;
}

int sum(int a, int b) { return add(a, b) + sub(a, b) + mul(a, b); }

TEST_CASE("Executor submit", "[submit]") {
  auto threadPool = arrow::GetCpuThreadPool();
  int a = 10;
  int b = 20;
  WHEN("submit without params or params") {
    std::vector<std::future<int>> futures;
    auto add_fut = threadPool->Submit([a, b]() { return add(a, b); });
    auto sub_fut = threadPool->Submit([a, b]() { return sub(a, b); });
    auto mul_fut = threadPool->Submit([a, b]() { return mul(a, b); });
    auto params_fut = threadPool->Submit(sum, a, b);
    futures.push_back(std::move(add_fut));
    futures.push_back(std::move(sub_fut));
    futures.push_back(std::move(mul_fut));
    futures.push_back(std::move(params_fut));
    THEN("the size and capacity change") {
      REQUIRE(futures[0].get() == 30);
      REQUIRE(futures[1].get() == -10);
      REQUIRE(futures[2].get() == 200);
      REQUIRE(futures[3].get() == 220);
    }
  }

  WHEN("submit with stop token") {
    arrow::StopSource stop_source;
    arrow::StopToken stop_token = stop_source.token();
    std::vector<std::future<int>> futures;
    auto add_fut = threadPool->Submit(stop_token, [a, b]() { return add(a, b); });
    auto sub_fut = threadPool->Submit(stop_token, [a, b]() { return sub(a, b); });
    auto mul_fut = threadPool->Submit(stop_token, [a, b]() { return mul(a, b); });
    auto params_fut = threadPool->Submit(sum, a, b); // no stop_token
    futures.push_back(std::move(add_fut));
    futures.push_back(std::move(sub_fut));
    futures.push_back(std::move(mul_fut));
    futures.push_back(std::move(params_fut));
    THEN("the size and capacity change") {
      REQUIRE(futures[0].get() == 30);
      REQUIRE(futures[1].get() == -10);
      REQUIRE(futures[2].get() == 200);
      REQUIRE(futures[3].get() == 220);
    }
  }
}