#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "src/cancel.h"
#include "src/io_util.h"
#include "src/macros.h"
#include "src/thread_pool.h"
using namespace arrow;

std::mutex consoleMutex;
void task(int id) {
  // Lock the console before printing
  std::lock_guard<std::mutex> lock(consoleMutex);
  // Get the ID of the current thread
  std::thread::id threadId = std::this_thread::get_id();

  std::cout << "Task " << id << " started by thread " << threadId << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "Task " << id << " completed by thread " << threadId << std::endl;
}

int main() {
  SetEnvVar("OMP_NUM_THREADS", "4");

  // Create a thread pool with 4 worker threads
  auto threadPool = GetCpuThreadPool();
  if (!threadPool) {
    std::cerr << "Failed to create thread pool" << std::endl;
    return 1;
  }

  // Submit tasks to the thread pool
  for (int i = 1; i <= 2; ++i) {
    threadPool->Spawn([i]() { task(i); });
  }

  // Wait for all tasks to complete
  threadPool->WaitForIdle();

  // Shutdown the thread pool
  threadPool->Shutdown();
}
