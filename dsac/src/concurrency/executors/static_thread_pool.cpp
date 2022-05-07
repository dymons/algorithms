#include <dsac/concurrency/executors/static_thread_pool.hpp>

namespace dsac {
static_thread_poll::static_thread_poll(std::size_t workers) {
  StartWorkerThreads(workers);
}

void static_thread_poll::StartWorkerThreads(std::size_t workers) {
  for (std::size_t i{}; i < workers; ++i) {
    workers_.emplace_back([this]() { WorkerRoutine(); });
  }
}

void static_thread_poll::WorkerRoutine() {
  while (true) {
    if (task task = tasks_.Pop(); task) {
      task();
    } else {
      break;
    }
  }
}

void static_thread_poll::Submit(task&& task) {
  tasks_.Push(std::move(task));
}

void static_thread_poll::Join() {
  for (auto& worker : workers_) {
    tasks_.Push({});  // Poison Pill
  }
  for (auto& worker : workers_) {
    worker.join();
  }
  workers_.clear();
}

base_executor_ptr make_static_thead_pool(std::size_t workers) {
  return dsac::make_shared<static_thread_poll>(workers);
}
}  // namespace dsac