
#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "src/io_util.h"
#include "src/thread_pool.h"

TEST_CASE("Executor capacity", "[capacity]") {
  WHEN("submit with env") {
    SetEnvVar("OMP_NUM_THREADS", "4");
    std::mutex consoleMutex;
    auto threadPool = arrow::GetCpuThreadPool();
    int cap = arrow::GetCpuThreadPoolCapacity();
    REQUIRE(threadPool);
    REQUIRE(cap == 4);
    for (int i = 1; i <= 2; ++i) {
      threadPool->Spawn([i, &consoleMutex]() {
        std::lock_guard<std::mutex> lock(consoleMutex);
        std::thread::id threadId = std::this_thread::get_id();

        std::cout << "Task " << i << " started by thread " << threadId << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Task " << i << " completed by thread " << threadId << std::endl;
      });
    }
    threadPool->WaitForIdle();
  }
}