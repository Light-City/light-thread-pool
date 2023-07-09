#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "src/cancel.h"
#include "src/io_util.h"
#include "src/macros.h"
#include "src/thread_pool.h"
using namespace arrow;

template <typename T>
static T add(T x, T y) {
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return x + y;
}
template <typename T>
static T sub(T x, T y) {
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return x - y;
}
template <typename T>
static T mul(T x, T y) {
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return x * y;
}

void status_callback(const Status& status) {
  std::cout << "status_callback: " << status.ToString() << std::endl;
}

int main() {
  arrow::StopSource stop_source;
  arrow::StopToken stop_token = stop_source.token();
  auto threadPool = GetCpuThreadPool();

  int a = 10;
  int b = 20;

  std::vector<std::future<int>> futures;
  // Submit multiple tasks
  auto add_fut = threadPool->Submit(arrow::TaskHints{}, stop_token, status_callback, [a, b]() { return add(a, b); });
  auto sub_fut = threadPool->Submit(stop_token, [a, b]() { return sub(a, b); });
  auto mul_fut = threadPool->Submit(stop_token, [a, b]() { return mul(a, b); });
  futures.push_back(std::move(add_fut));
  futures.push_back(std::move(sub_fut));
  futures.push_back(std::move(mul_fut));
  stop_source.RequestStop();

  // Retrieve the results
  for (auto& future : futures) {
    try {
      int result = future.get();
      std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) { /* will throw error. */
      std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
  }

  return 0;
}
